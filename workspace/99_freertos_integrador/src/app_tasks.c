#include "app_tasks.h"

// Cola para datos del ADC
xQueueHandle queue_adc;
// Cola para selecion de valor para el display
xQueueHandle queue_display_variable;

/**
 * @brief Activa una secuencia de conversion cada 0.25 segundos
 */
void task_adc_read(void *params) {

	while(1) {
		// Inicio una conversion
		ADC_DoSoftwareTriggerConvSeqA(ADC0);
		// Bloqueo la tarea por 250 ms
		vTaskDelay(250);
	}
}

/**
 * @brief Lee los valores de los botones para definir que valor mostrar
 */
void task_btn(void *params) {
	// Dato para pasar
	display_variable_t variable = kDISPLAY_TEMP;

	while(1) {
		// Veo que boton se presiono
		if(!wrapper_btn_get(USR_BTN)) {
			// Antirebote
			vTaskDelay(20);
			if(!wrapper_btn_get(USR_BTN)) {
				// USR Button para temperatura
				variable = kDISPLAY_TEMP;
			}
		}
		else if(!wrapper_btn_get(ISP_BTN)) {
			// Antirebote
			vTaskDelay(20);
			if(!wrapper_btn_get(ISP_BTN)) {
				// ISP Button para la referencia
				variable = kDISPLAY_REF;
			}
		}
		// Mando datos en la cola
		xQueueOverwrite(queue_display_variable, &variable);
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

	while(1) {
		// Veo que variable hay que mostrar
		xQueuePeek(queue_display_variable, &variable, portMAX_DELAY);
		// Leo los datos del ADC
		xQueuePeek(queue_adc, &data, portMAX_DELAY);
		// Veo cual tengo que mostrar
		if(variable == kDISPLAY_TEMP) {
			// Calculo la temperatura
			val = (uint8_t)(100 * (3.3 * data.temp_raw / 4095.0));
		}
		else {
			// Calculo la referencia
			val = (uint8_t)(30.0 * data.ref_raw / 4095.0);
		}
		// Muestro el numero
		wrapper_display_off();
		wrapper_display_write((uint8_t)(val / 10));
		wrapper_display_on(COM_1);
		vTaskDelay(20);
		wrapper_display_off();
		wrapper_display_write((uint8_t)(val % 10));
		wrapper_display_on(COM_2);
		vTaskDelay(20);
	}
}

/**
 * @brief Handler para la interrupcion del ADC Sequence A
 */
void ADC_SEQA_IRQHandler(void) {
	// Variable de cambio de contexto
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	// Verifico que se haya terminado la conversion correctamente
	if(kADC_ConvSeqAInterruptFlag == (kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0))) {
		// Limpio flag de interrupcion
		ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);
		// Resultado de conversion
		adc_result_info_t temp_info, ref_info;
		// Leo el valor del ADC
		ADC_GetChannelConversionResult(ADC0, REF_POT_CH, &ref_info);
		// Leo el valor del ADC
		ADC_GetChannelConversionResult(ADC0, LM35_CH, &temp_info);
		// Estructura de datos para mandar
		adc_data_t data = {
			.temp_raw = (uint16_t)temp_info.result,
			.ref_raw = (uint16_t)ref_info.result
		};
		// Mando por la cola los datos
		xQueueOverwriteFromISR(queue_adc, &data, &xHigherPriorityTaskWoken);
		// Veo si hace falta un cambio de contexto
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}
