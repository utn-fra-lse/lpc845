#include "isr.h"

/**
 * @brief Callback para interrupción por flancos del infrarojo
 * @param pintr numero de interrupción
 */
void cny70_callback(pint_pin_int_t pintr, uint32_t pmatch_status) {
	// Tarea de prioridad alta?
	int32_t higher_task = 0;
	// Doy el semáforo para la tarea
	xSemaphoreGiveFromISR(semphr_buzz, &higher_task);
	// Limpio flag de interrupción
	PINT_PinInterruptClrStatus(PINT, pintr);
	// Retorno a tarea de alta prioridad
	portYIELD_FROM_ISR(higher_task);
}

/**
 * @brief Callback para interrupción por flanco del botón de user
 * @param pintr numero de interrupción
 */
void usr_callback(pint_pin_int_t pintr, uint32_t pmatch_status) {
	// Tarea de prioridad alta?
	int32_t higher_task = 0;
	// Doy el semáforo para la tarea
	xSemaphoreGiveFromISR(semphr_usr, &higher_task);
	// Limpio flag de interrupción
	PINT_PinInterruptClrStatus(PINT, pintr);
	// Retorno a tarea de alta prioridad
	portYIELD_FROM_ISR(higher_task);
}

/**
 * @brief Handler para la interrupcion del ADC Sequence A
 */
void ADC0_SEQA_IRQHandler(void) {
	// Variable de cambio de contexto
	int32_t higher_task = 0;
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
			.temp_raw = (uint16_t) 4095 - temp_info.result,
			.ref_raw = (uint16_t) 4095 - ref_info.result
		};
		// Mando por la cola los datos
		xQueueOverwriteFromISR(queue_adc, &data, &higher_task);
		// Veo si hace falta un cambio de contexto
		portYIELD_FROM_ISR(higher_task);
	}
}

/**
 * @brief Handler para la interrupción del touch
 */
void CMP_CAPT_IRQHandler(void) {
	// Variable de cambio de contexto
	int32_t higher_task = 0;
	// Limpio interrupción
	CAPT_ClearInterruptStatusFlags(CAPT, kCAPT_InterruptOfPollDoneStatusFlag);
	// Doy el semáforo si se presionó el touch
	if(wrapper_touch_is_touched()) {
		xSemaphoreGiveFromISR(semphr_touch, &higher_task);
	}
	// Veo si hace falta un cambio de contexto
	portYIELD_FROM_ISR(higher_task);
}