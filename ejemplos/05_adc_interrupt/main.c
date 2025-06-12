#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_swm.h"
#include "fsl_power.h"
#include "fsl_adc.h"

// Canal de ADC para el potenciometro
#define ADC_POT_CH		0

// Flag para verificar que la conversion se termino
bool adc_conversion_done = false;

/**
 * @brief Programa principal
 */
int main(void) {
	// Inicializacion de console
    BOARD_InitDebugConsole();

    // Activo clock de matriz de conmutacion
    CLOCK_EnableClock(kCLOCK_Swm);
    // Configuro la funcion de ADC en el canal del potenciometro
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN0, true);
    // Desactivo clock de matriz de conmutacion
    CLOCK_DisableClock(kCLOCK_Swm);

    // Elijo clock desde el FRO con divisor de 1 (30MHz)
    CLOCK_Select(kADC_Clk_From_Fro);
    CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1);

    // Prendo el ADC
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);
    // Obtengo frecuencia deseada y calibro ADC
	uint32_t frequency = CLOCK_GetFreq(kCLOCK_Fro) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk);
	ADC_DoSelfCalibration(ADC0, frequency);
	// Configuracion del ADC
	adc_config_t adc_config = {
		.clockMode = kADC_ClockSynchronousMode,
		.clockDividerNumber = 1,
		.enableLowPowerMode = false,
		.voltageRange = kADC_HighVoltageRange
	};
    // Habilito el ADC
	ADC_Init(ADC0, &adc_config);

	// Configuracion para las conversiones
	adc_conv_seq_config_t adc_sequence = {
		.channelMask = 1 << ADC_POT_CH,							// Elijo el canal del potenciometro
		.triggerMask = 0,										// No hay trigger por hardware
		.triggerPolarity = kADC_TriggerPolarityPositiveEdge,	// Flanco ascendente
		.enableSyncBypass = false,								// Sin bypass de trigger
		.interruptMode = kADC_InterruptForEachSequence			// Interrupciones para cada secuencia
	};
	// Configuro y habilito secuencia A
	ADC_SetConvSeqAConfig(ADC0, &adc_sequence);
	ADC_EnableConvSeqA(ADC0, true);

	// Habilito interrupcion para el ADC y en el NVIC
    ADC_EnableInterrupts(ADC0, kADC_ConvSeqAInterruptEnable);
    NVIC_EnableIRQ(ADC0_SEQA_IRQn);

	// Inicio primer conversion
	ADC_DoSoftwareTriggerConvSeqA(ADC0);

    while(1) {
    	// Verifico si se hizo la conversion
    	if(adc_conversion_done) {
    		// Resultado de conversion
    		adc_result_info_t adc_info;
    		// Leo el valor del ADC
    		ADC_GetChannelConversionResult(ADC0, ADC_POT_CH, &adc_info);
        	// Muestro resultado
        	PRINTF(
    			"El resultado del canal %ld en el PIO0_7 dio %d\n",
    			adc_info.channelNumber,
    			adc_info.result
        	);
        	// Limpio el flag
        	adc_conversion_done = false;
        	// Inicio una nueva conversion
        	ADC_DoSoftwareTriggerConvSeqA(ADC0);
    	}
    }
    return 0;
}


/**
 * @brief Handler para la interrupcion del ADC Sequence A
 */
void ADC0_SEQA_IRQHandler(void) {
	// Verifico que se haya terminado la conversion correctamente
	if(kADC_ConvSeqAInterruptFlag == (kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0))) {
		// Limpio flag de interrupcion
		ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);
		// Aviso que se termino la conversion
		adc_conversion_done = true;
	}
}