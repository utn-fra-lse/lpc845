#include "app_tasks.h"

// Cola para datos del ADC
xQueueHandle queue_adc;
// Cola para selecion de valor para el display
xQueueHandle queue_display_variable;
// Cola para datos de luminosidad
xQueueHandle queue_lux;
// Cola para datos del display
xQueueHandle queue_display;

// Semáforo para interrupción del infrarojo
xSemaphoreHandle semphr_buzz;
// Semáforo para interrupción del user button
xSemaphoreHandle semphr_usr;
// Semáforo para interrupción del touch
xSemaphoreHandle semphr_touch;
// Semáforo para contador
xSemaphoreHandle semphr_counter;
// Semáforo mutex para el display
xSemaphoreHandle semphr_mutex;

// Handler para la tarea de display write
TaskHandle_t handle_display;

/**
 * @brief Inicializa todos los perifericos y colas
 */
void task_init(void *params) {
	// Inicializo semáforos
	semphr_buzz = xSemaphoreCreateBinary();
	semphr_usr = xSemaphoreCreateBinary();
	semphr_touch = xSemaphoreCreateBinary();
	semphr_counter = xSemaphoreCreateCounting(99, 30);
	semphr_mutex = xSemaphoreCreateMutex();

	// Inicializo colas
	queue_adc = xQueueCreate(1, sizeof(adc_data_t));
	queue_display_variable = xQueueCreate(1, sizeof(display_variable_t));
	queue_lux = xQueueCreate(1, sizeof(uint16_t));
	queue_display = xQueueCreate(1, sizeof(uint16_t));
	
	// Inicializacion de GPIO
	wrapper_gpio_init(0);
	wrapper_gpio_init(1);
	// Inicialización del LED
	wrapper_output_init((gpio_t){LED}, true);
	// Inicialización del buzzer
	wrapper_output_init((gpio_t){BUZZER}, false);
	// Inicialización del enable del CNY70
	wrapper_output_init((gpio_t){CNY70_EN}, true);
	// Configuro el ADC
	wrapper_adc_init();
	// Configuro el display
	wrapper_display_init();
	// Configuro botones
	wrapper_btn_init();
	// Configuro interrupción por flancos para el infrarojo y para el botón del user
	wrapper_gpio_enable_irq((gpio_t){CNY70}, kPINT_PinIntEnableBothEdges, cny70_callback);
	wrapper_gpio_enable_irq((gpio_t){USR_BTN}, kPINT_PinIntEnableFallEdge, usr_callback);
	// Inicializo el PWM
	wrapper_pwm_init();
	// Inicializo I2C y Bh1750
	wrapper_i2c_init();
	wrapper_bh1750_init();
	// Inicializo el pulsador capacitivo
	wrapper_touch_init();

	// Elimino tarea para liberar recursos
	vTaskDelete(NULL);
}

/**
 * @brief Activa una secuencia de conversion cada 0.25 segundos
 */
void task_adc(void *params) {

	while(1) {
		// Inicio una conversion
		ADC_DoSoftwareTriggerConvSeqA(ADC0);
		// Bloqueo la tarea por 250 ms
		vTaskDelay(pdMS_TO_TICKS(250));
	}
}

/**
 * @brief Lee los valores de los botones para definir que valor mostrar
 */
void task_display_change(void *params) {
	// Dato para pasar
	display_variable_t variable = kDISPLAY_TEMP;

	while(1) {
		// Escribe el dato en la cola
		xQueueOverwrite(queue_display_variable, &variable);
		// Intenta tomar el semáforo
		xSemaphoreTake(semphr_usr, portMAX_DELAY);
		// Si se presionó, cambio la variable
		variable = (variable == kDISPLAY_TEMP)? kDISPLAY_REF : kDISPLAY_TEMP;
	}
}

/**
 * @brief Escribe valores en el display
 */
void task_control(void *params) {
	// Variable a mostrar
	display_variable_t variable = kDISPLAY_TEMP;
	// Valores de ADC
	adc_data_t data = {0};
	// Valor a mostrar
	uint16_t val = 0;

	while(1) {
		// Veo que variable hay que mostrar
		xQueuePeek(queue_display_variable, &variable, portMAX_DELAY);
		// Leo los datos del ADC
		xQueuePeek(queue_adc, &data, portMAX_DELAY);
		// Veo cual tengo que mostrar
		val = (variable == kDISPLAY_TEMP)? data.temp_raw : data.ref_raw;
		val = 30 * val / 4095;
		// Escribo en la cola del display si puedo tomar el mutex
		xSemaphoreTake(semphr_mutex, portMAX_DELAY);
		xQueueOverwrite(queue_display, &val);
		xSemaphoreGive(semphr_mutex);

		vTaskDelay(pdMS_TO_TICKS(50));
	}
}

/**
 * @brief Tarea que escribe un número en el display
 */
void task_display(void *params) {
	// Variable con el dato para escribir
	uint8_t data;

	while(1) {
		// Mira el dato que haya en la cola
		if(!xQueuePeek(queue_display, &data, pdMS_TO_TICKS(100))) { continue; }
		// Muestro el número
		wrapper_display_off();
		wrapper_display_write((uint8_t)(data / 10));
		wrapper_display_on((gpio_t){COM_1});
		vTaskDelay(pdMS_TO_TICKS(10));
		wrapper_display_off();
		wrapper_display_write((uint8_t)(data % 10));
		wrapper_display_on((gpio_t){COM_2});
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

/**
 * @brief Actualiza el duty del PWM
 */
void task_pwm(void *params) {
	// Variable para guardar los datos del ADC
	adc_data_t data = {0};

	while(1) {
		// Bloqueo hasta que haya algo que leer
		xQueuePeek(queue_adc, &data, portMAX_DELAY);
		// Calculo la diferencia
		int16_t err = 100 * (data.ref_raw - data.temp_raw) / 4095;
		// Actualizo el duty
		if(err > 0) {
			// Referencia por arriba, quiero calentar -> LED rojo
			wrapper_pwm_update_bled(0);
			wrapper_pwm_update_rled(err);
		}
		else {
			// Referencia por debajo, quiero enfriar -> LED azul
			wrapper_pwm_update_rled(0);
			wrapper_pwm_update_bled(-err);
		}
		vTaskDelay(pdMS_TO_TICKS(20));
	}
}

/**
 * @brief Lee periodicamente el valor de intensidad luminica
 */
void task_bh1750(void *params) {
	// Valor de intensidad luminica
	uint16_t lux = 0;

	while(1) {
		// Bloqueo por 160 ms (requisito)
		vTaskDelay(pdMS_TO_TICKS(200));
		// Leo el valor de lux
		lux = wrapper_bh1750_read();
		// Muestro por consola
		xQueueOverwrite(queue_lux, &lux);
	}
}

/**
 * @brief Dibuja una animacion sobre el 7 segmentos
 */
void task_animation(void *params) {
	// Segmentos usados
	gpio_t pins[] = { {SEG_A}, {SEG_B}, {SEG_C}, {SEG_D}, {SEG_E}, {SEG_F} };

	while(1) {
		// Reviso el estado del pulsador
		if(!wrapper_btn_get_with_debouncing_with_pull_up((gpio_t){ISP_BTN})) {
			// Si no está presionado, libero la tarea
			vTaskResume(handle_display);
			vTaskDelay(pdMS_TO_TICKS(100));
			continue;
		}
		// Suspendo la tarea que dibuja los numeros
		vTaskSuspend(handle_display);
		// Prendo ambos segmentos
		wrapper_display_on_both();
		// Prendo de a uno los segmentos
		for(uint8_t i = 0; i < sizeof(pins) / sizeof(gpio_t); i++) {
			// Apago todos los segmentos
			wrapper_display_segments_off();
			wrapper_display_segment_on(pins[i]);
			vTaskDelay(pdMS_TO_TICKS(50));
		}
	}
}

/**
 * @brief Tarea que parpadea el LED de acuerdo a la intensidad lumínica
 */
void task_blinky(void *params) {
	// Variable para guardar el tiempo en ms de bloqueo
	uint16_t blocking_time;

	while(1) {
		// Lee el último valor de luminosidad
		xQueuePeek(queue_lux, &blocking_time, portMAX_DELAY);
		// Máximo es aprox 30000 entonces 3000 ms como máximo
		blocking_time /= 10;
		// Conmuto salida
		wrapper_output_toggle((gpio_t){LED});
		// Bloqueo el tiempo que se indique de la cola
		vTaskDelay(pdMS_TO_TICKS(blocking_time));
	}
}

/**
 * @brief Tarea que hace sonar el buzzer
 */
void task_buzzer(void *params) {

	while(1) {
		// Intenta tomar el semáforo
		xSemaphoreTake(semphr_buzz, portMAX_DELAY);
		// Conmuto el buzzer
		wrapper_output_toggle((gpio_t){BUZZER});
	}
}

/**
 * @brief Tarea que decrementa el contador
 */
void task_counter(void *params) {
	while(1) {
		// Decrementa la cuenta cada un segundo
		xSemaphoreTake(semphr_counter, 0);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

/**
 * @brief Tarea que manualmente controla el contador
 */
void task_counter_btns(void *params) {

	while(1) {
		// Intenta tomar el semáforo
		xSemaphoreTake(semphr_touch, portMAX_DELAY);
		// Toma el mutex para bloquear la otra tarea que escribe el display
		xSemaphoreTake(semphr_mutex, portMAX_DELAY);
		// Verifica qué pulsador se presionó
		if(wrapper_btn_get_with_debouncing_with_pull_up((gpio_t){S1_BTN})) {
			// Decrementa la cuenta del semáforo
			xSemaphoreTake(semphr_counter, 0);
		}
		else if(wrapper_btn_get_with_debouncing_with_pull_up((gpio_t){S2_BTN})) {
			// Incrementa la cuenta del semáforo
			xSemaphoreGive(semphr_counter);
		}
		// Escribe en el display
		uint16_t data = uxSemaphoreGetCount(semphr_counter);
		xQueueOverwrite(queue_display, &data);
		// Demora chica para evitar que detecte muy rápido que se presionó
		vTaskDelay(pdMS_TO_TICKS(30));
		// Devuelve el mutex
		xSemaphoreGive(semphr_mutex);
	}
}