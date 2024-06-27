#include "app_tasks.h"

/**
 * @brief Tarea de inicializacion
 */
void task_init(void *params) {

	// Configuro el ADC
	wrapper_adc_init();

	// Elimino la tarea
	vTaskDelete(NULL);
}


/**
 * @brief Handler para la interrupcion del ADC Sequence A
 */
void ADC_SEQA_IRQHandler(void) {
	// Verifico que se haya terminado la conversion correctamente
	if(kADC_ConvSeqAInterruptFlag == (kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0))) {
		// Limpio flag de interrupcion
		ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);
		// Resultado de conversion
		adc_result_info_t adc_info;
		// Leo el valor del ADC
		ADC_GetChannelConversionResult(ADC0, REF_POT_CH, &adc_info);
		// Leo potenciometro (0 a 30 grados)
		float ref = 30 * adc_info.result / 4095.0;
		// Leo el valor del ADC
		ADC_GetChannelConversionResult(ADC0, LM35_CH, &adc_info);
		// Leo el LM35
		float temp = 330 * adc_info.result / 4095.0;
	}
}
