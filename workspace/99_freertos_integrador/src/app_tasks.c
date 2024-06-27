#include "app_tasks.h"

// Cola para datos del ADC
xQueueHandle queue_adc;

/**
 * @brief Inicializacion de perifericos
 */
void task_init(void *params) {
	// Configuro el ADC
	wrapper_adc_init();

	// Elimino la tarea
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
		vTaskDelay(250);
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
		xQueueSendToBackFromISR(queue_adc, &data, &xHigherPriorityTaskWoken);
		// Veo si hace falta un cambio de contexto
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}
