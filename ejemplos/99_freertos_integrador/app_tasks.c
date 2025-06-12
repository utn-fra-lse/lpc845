#include "app_tasks.h"

// Cola para datos del ADC
xQueueHandle queue_adc;
// Cola para selecion de valor para el display
xQueueHandle queue_display_variable;
// Cola para datos de temperatura
xQueueHandle queue_temp;
// Cola para datos de luminosidad
xQueueHandle queue_lux;

// Semáforo para interrupción del infrarojo
xSemaphoreHandle semphr_buzz;
// Semáforo para interrupción del user button
xSemaphoreHandle semphr_usr;

// Handler para la tarea de display write
TaskHandle_t handle_display;

/**
 * @brief Inicializa todos los perifericos y colas
 */
void task_init(void *params) {
	// Inicializacion de GPIO
	wrapper_gpio_init(0);
	wrapper_gpio_init(1);
	// Inicialización del LED
	wrapper_output_init((gpio_t){BLED}, true);
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

	// Inicializo colas
	queue_adc = xQueueCreate(1, sizeof(adc_data_t));
	queue_display_variable = xQueueCreate(1, sizeof(display_variable_t));
	queue_temp = xQueueCreate(1, sizeof(temp_data_t));
	queue_lux = xQueueCreate(1, sizeof(uint16_t));
	// Inicializo semáforos
	semphr_buzz = xSemaphoreCreateBinary();
	semphr_usr = xSemaphoreCreateBinary();

	// Elimino tarea para liberar recursos
	vTaskDelete(NULL);
}

/**
 * @brief Activa una secuencia de conversion cada 0.25 segundos
 */
void task_adc_read(void *params) {

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
void task_btn(void *params) {
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
void task_display_write(void *params) {
	// Variable a mostrar
	display_variable_t variable = kDISPLAY_TEMP;
	// Valores de ADC
	adc_data_t data = {0};
	// Valor a mostrar
	uint8_t val = 0;
	// GPIOs para pines comunes de los segmentos
	gpio_t com_1 = {COM_1}, com_2 = {COM_2};

	while(1) {
		// Veo que variable hay que mostrar
		xQueuePeek(queue_display_variable, &variable, portMAX_DELAY);
		// Leo los datos del ADC
		xQueuePeek(queue_adc, &data, portMAX_DELAY);
		// Calculo las temperaturas
		temp_data_t temps = {
			.temp_lm35 = (30.0 * data.temp_raw / 4095.0),
			.temp_ref = (30.0 * data.ref_raw / 4095.0)
		};
		// Mando a la cola para el PWM
		xQueueOverwrite(queue_temp, &temps);
		// Veo cual tengo que mostrar
		if(variable == kDISPLAY_TEMP) {
			// Calculo la temperatura
			val = (uint8_t) temps.temp_lm35;
		}
		else {
			// Calculo la referencia
			val = (uint8_t) temps.temp_ref;
		}
		// Muestro el numero
		wrapper_display_off();
		wrapper_display_write((uint8_t)(val / 10));
		wrapper_display_on(com_1);
		vTaskDelay(pdMS_TO_TICKS(10));
		wrapper_display_off();
		wrapper_display_write((uint8_t)(val % 10));
		wrapper_display_on(com_2);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

/**
 * @brief Actualiza el duty del PWM
 */
void task_pwm(void *params) {
	// Variable para guardar los datos del ADC
	temp_data_t temps = {0};

	while(1) {
		// Bloqueo hasta que haya algo que leer
		xQueueReceive(queue_temp, &temps, portMAX_DELAY);
		// Calculo la diferencia
		float err = 5 * (temps.temp_ref - temps.temp_lm35);
		// Actualizo el duty
		wrapper_pwm_update((int16_t)err);
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
	gpio_t isp_btn = {ISP_BTN};

	while(1) {
		// Reviso el estado del pulsador
		if(!wrapper_btn_get_with_debouncing_with_pull_up(isp_btn)) {
			// Si no está presionado, libero la tarea
			vTaskResume(handle_display);
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
	// Salida con la que trabajar
	gpio_t led = {BLED};

	while(1) {
		// Lee el último valor de luminosidad
		xQueuePeek(queue_lux, &blocking_time, portMAX_DELAY);
		// Máximo es aprox 30000 entonces 3000 ms como máximo
		blocking_time /= 10;
		// Conmuto salida
		wrapper_output_toggle(led);
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