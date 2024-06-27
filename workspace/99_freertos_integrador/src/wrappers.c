#include "wrappers.h"

/**
 * @brief Wrapper para inicializacion del ADC
 */
void wrapper_adc_init(void) {
    // Activo clock de matriz de conmutacion
    CLOCK_EnableClock(kCLOCK_Swm);
    // Configuro la funcion de ADC en el canal del LM35
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN7, true);
    // Configuro la funcion de ADC en el canal del potenciometro
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN8, true);
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
	// Configuracion por defecto del ADC
	adc_config_t adc_config;
	ADC_GetDefaultConfig(&adc_config);
    // Habilito el ADC
	ADC_Init(ADC0, &adc_config);
	// Configuracion para las conversiones
	adc_conv_seq_config_t adc_sequence = {
		.channelMask = 1 << LM35_CH | 1 << REF_POT_CH,			// Elijo los canales
		.triggerMask = 0,										// No hay trigger por hardware
		.triggerPolarity = kADC_TriggerPolarityPositiveEdge,	// Flanco ascendente
		.enableSyncBypass = false,								// Sin bypass de trigger
		.interruptMode = kADC_InterruptForEachSequence			// Interrupciones para cada conversion
	};
	// Configuro y habilito secuencia A
	ADC_SetConvSeqAConfig(ADC0, &adc_sequence);
	ADC_EnableConvSeqA(ADC0, true);

	// Habilito interrupcion para el ADC y en el NVIC
    ADC_EnableInterrupts(ADC0, kADC_ConvSeqAInterruptEnable);
    NVIC_EnableIRQ(ADC0_SEQA_IRQn);
}

/**
 * @brief Wrapper para inicializacion del display 7 segmentos
 */
void wrapper_display_init(void) {

	// Inicializo el puerto
	GPIO_PortInit(GPIO, 0);
	// Inicializo los pines como salidas
	gpio_pin_direction_t config = { kGPIO_DigitalOutput, true };
	uint32_t pins[] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, COM_1, COM_2 };
	for(uint8_t i = 0; i < sizeof(pins) / sizeof(uint32_t); i++) {
		GPIO_PinInit(GPIO, 0, pins[i], &config);
		GPIO_PinWrite(GPIO, 0, pins[i], 1);
	}
}

/**
 * @brief Escribe el numero de un digito en el display
 * @param number es el numero que se quiere escribir
 */
void wrapper_display_write(uint8_t number) {
	// Array con valores para los pines
	uint8_t values[] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6 };
	// Array con los segmentos
	uint32_t pins[] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G };

	for(uint8_t i = 0; i < sizeof(pins) / sizeof(uint32_t); i++) {
		// Escribo el valor del bit en el segmento que corresponda
		uint32_t val = (values[number] & (1 << i))? 1 : 0;
		GPIO_PinWrite(GPIO, 0, pins[i], val);
	}
}
