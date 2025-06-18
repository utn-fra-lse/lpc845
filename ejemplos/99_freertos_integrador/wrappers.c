#include "wrappers.h"

// Variable privada para registrar el evento del PWM
static uint32_t pwm_bled_event = 0, pwm_rled_event = 0;

/**
 * @brief Wrapper para inicializacion del ADC
 */
void wrapper_adc_init(void) {
	// Activo clock de matriz de conmutacion
	CLOCK_EnableClock(kCLOCK_Swm);
	// Configuro la funcion de ADC en el canal del LM35
	// SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN7, true);
	SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN0, true);
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
 * @brief Wrapper para inicializacion de los botones
 */
void wrapper_btn_init(void) {
	// Inicializo botones
	gpio_pin_config_t config = { kGPIO_DigitalInput };
	gpio_t inputs[] = { {S1_BTN}, {S2_BTN}, {USR_BTN}, {ISP_BTN}, {CNY70} };
	for(uint32_t i = 0; i < sizeof(inputs) / sizeof(gpio_t); i++) { 
		GPIO_PinInit(GPIO_DESTRUCT(inputs[i]), &config);
	}
}

/**
 * @brief Wrapper para habilitar una interrupción en una entrada
 * @param gpio estructura de GPIO
 * @param edge kPINT_PinIntEnableRiseEdge, kPINT_PinIntEnableFallEdge, kPINT_PinIntEnableBothEdges
 */
void wrapper_gpio_enable_irq(gpio_t gpio, pint_pin_enable_t edge, pint_cb_t callback) {
	// Variable para guardar el numero de interrupción
	static uint32_t pint_n = 0;
	// Solo la primera vez que se configura la interrupción
	if(pint_n == 0) { PINT_Init(PINT); }
	// Asigno el pin a la interrupción
	SYSCON->PINTSEL[pint_n] = wrapper_gpio_get_pin(gpio);
	// PINT interrupt para el flanco indicado
	PINT_PinInterruptConfig(PINT, (pint_pin_int_t)pint_n, edge, callback);
	PINT_EnableCallbackByIndex(PINT, (pint_pin_int_t)pint_n++);
}

/**
 * @brief Wrapper para inicializacion del display 7 segmentos
 */
void wrapper_display_init(void) {
	// Inicializo los pines como salidas
	gpio_pin_config_t config = { kGPIO_DigitalOutput, true };
	gpio_t pins[] = { {SEG_A}, {SEG_B}, {SEG_C}, {SEG_D}, {SEG_E}, {SEG_F}, {SEG_G}, {COM_1}, {COM_2} };
	for(uint8_t i = 0; i < sizeof(pins) / sizeof(gpio_t); i++) {
		GPIO_PinInit(GPIO_DESTRUCT(pins[i]), &config);
	}
}

/**
 * @brief Escribe el numero de un digito en el display
 * @param number es el numero que se quiere escribir
 */
void wrapper_display_write(uint8_t number) {
	// Array con valores para los pines
	uint8_t values[] = { ~0x3f, ~0x6, ~0x5b, ~0x4f, ~0x66, ~0x6d, ~0x7d, ~0x7, ~0x7f, ~0x6f };
	// Array con los segmentos
	gpio_t pins[] = { {SEG_A}, {SEG_B}, {SEG_C}, {SEG_D}, {SEG_E}, {SEG_F}, {SEG_G} };

	for(uint8_t i = 0; i < sizeof(pins) / sizeof(gpio_t); i++) {
		// Escribo el valor del bit en el segmento que corresponda
		uint32_t val = (values[number] & (1 << i))? 1 : 0;
		GPIO_PinWrite(GPIO_DESTRUCT(pins[i]), val);
	}
}

/**
 * @brief Wrapper para inicializacion del PWM para el LED
 */
void wrapper_pwm_init(void) {
	// Conecto la salida 4 del SCT al LED azul
    CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT0, kSWM_PortPin_P1_0 + wrapper_gpio_get_pin((gpio_t){BLED}));
		SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT1, kSWM_PortPin_P1_0 + wrapper_gpio_get_pin((gpio_t){RLED}));
    CLOCK_DisableClock(kCLOCK_Swm);

    // Eligo el clock para el Timer
    uint32_t sctimer_clock = CLOCK_GetFreq(kCLOCK_Fro);
    // Configuracion del SCT Timer
    sctimer_config_t sctimer_config;
    SCTIMER_GetDefaultConfig(&sctimer_config);
    SCTIMER_Init(SCT0, &sctimer_config);

    // Configuro el PWM para el LED azul
    sctimer_pwm_signal_param_t bled_pwm_config = {
			.output = kSCTIMER_Out_0,			// Salida del Timer
			.level = kSCTIMER_LowTrue,		// Logica negativa
			.dutyCyclePercent = 0					// Apagado
    };

		// Inicializo el PWM
    SCTIMER_SetupPwm(
			SCT0,
			&bled_pwm_config,
			kSCTIMER_CenterAlignedPwm,
			1000,
			sctimer_clock,
			&pwm_bled_event
		);

		// Configuro el PWM
    sctimer_pwm_signal_param_t rled_pwm_config = {
			.output = kSCTIMER_Out_1,			// Salida del Timer
			.level = kSCTIMER_LowTrue,		// Logica negativa
			.dutyCyclePercent = 0					// Apagado
    };

				// Inicializo el PWM
    SCTIMER_SetupPwm(
			SCT0,
			&rled_pwm_config,
			kSCTIMER_CenterAlignedPwm,
			1000,
			sctimer_clock,
			&pwm_rled_event
		);

    // Inicializo el Timer
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);
}

/**
 * @brief Wrapper privado para inicializar el PWM
 * @param out salida de SCTimer
 * @param duty ancho de pulso de 0 a 100
 * @param event número de evento del PWM
 */
static void wrapper_pwm_update_led(sctimer_out_t out, int16_t duty, uint32_t event) {
	// Verifico que no se haya excedido de los limites
	if(duty < 0) { duty = 0; }
	else if(duty > 100) { duty = 100; }
	// Actualizo el duty
	SCTIMER_UpdatePwmDutycycle(SCT0, out, duty, event);
}

/**
 * @brief Wrapper para actualizar el valor de duty del PWM del LED azul
 */
void wrapper_pwm_update_bled(int16_t duty) {
	// Invoco al wrapper general
	wrapper_pwm_update_led(kSCTIMER_Out_0, duty, pwm_bled_event);
}

/**
 * @brief Wrapper para actualizar el valor de duty del PWM del LED rojo
 */
void wrapper_pwm_update_rled(int16_t duty) {
	// Invoco al wrapper general
	wrapper_pwm_update_led(kSCTIMER_Out_1, duty, pwm_rled_event);
}

/**
 * @brief Wrapper que inicializa el I2C
 */
void wrapper_i2c_init(void) {
	// Inicializo el clock del I2C1
	CLOCK_Select(kI2C1_Clk_From_MainClk);
	// Asigno las funciones de I2C1 a los pines 26 y 27
	CLOCK_EnableClock(kCLOCK_Swm);
	SWM_SetMovablePinSelect(SWM0, kSWM_I2C1_SDA, kSWM_PortPin_P0_27);
	SWM_SetMovablePinSelect(SWM0, kSWM_I2C1_SCL, kSWM_PortPin_P0_26);
	CLOCK_DisableClock(kCLOCK_Swm);

	// Configuracion de master para el I2C
	i2c_master_config_t config;
	I2C_MasterGetDefaultConfig(&config);
	config.baudRate_Bps = 400000;
	I2C_MasterInit(I2C1, &config, SystemCoreClock);
}

/**
 * @brief Wrapper que inicializa el BH1750
 */
void wrapper_bh1750_init(void) {
	// Comandos
	uint8_t cmd[] = { 0x01, 0x10 };
	// Comando de power on
	I2C_MasterStart(I2C1, BH1750_ADDR, kI2C_Write);
	I2C_MasterWriteBlocking(I2C1, &cmd[0], 1, kI2C_TransferDefaultFlag);
	I2C_MasterStop(I2C1);
	// Comando de medicion continua a 1 lux de resolucion
	I2C_MasterStart(I2C1, BH1750_ADDR, kI2C_Write);
	I2C_MasterWriteBlocking(I2C1, &cmd[1], 1, kI2C_TransferDefaultFlag);
	I2C_MasterStop(I2C1);
}

/**
 * @brief Wrapper para lectura del BH1750 en modo continuo
 * @return intensidad luminica en luxes
 */
float wrapper_bh1750_read(void) {
	// Resultado
	uint8_t res[2] = {0};
	// Lectura del sensor
	I2C_MasterRepeatedStart(I2C1, BH1750_ADDR, kI2C_Read);
	I2C_MasterReadBlocking(I2C1, res, 2, kI2C_TransferDefaultFlag);
	I2C_MasterStop(I2C1);
	// Devuelvo el resultado
	return ((res[0] << 8) + res[1]) / 1.2;
}

/**
 * @brief Wrapper que inicializa el pulsador capacitivo 
 */
void wrapper_touch_init(void) {
	// Habilita las funciones de táctil capacitivo en los pines
	CLOCK_EnableClock(kCLOCK_Swm);
	SWM_SetFixedPinSelect(SWM0, kSWM_CAPT_X0, true);
	SWM_SetFixedPinSelect(SWM0, kSWM_CAPT_YH, true);
	SWM_SetFixedPinSelect(SWM0, kSWM_CAPT_YL, true);
	CLOCK_DisableClock(kCLOCK_Swm);

	// Saca pull ups y pull downs
	CLOCK_EnableClock(kCLOCK_Iocon);
	IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO1_8, IOCON_CAPT_CONFIG);
	IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO1_9, IOCON_CAPT_CONFIG);
	IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_31, IOCON_CAPT_CONFIG);
	CLOCK_DisableClock(kCLOCK_Iocon);

	// Selecciona el clock de base
	CLOCK_Select(kCAPT_Clk_From_Fro);
	POWER_DisablePD(kPDRUNCFG_PD_ACMP);

	// Inicialización básica del táctil agregando el pin X0
	capt_config_t config;
	CAPT_GetDefaultConfig(&config);
	config.enableXpins = kCAPT_X0Pin;
	CAPT_Init(CAPT, &config);
	// Habilita interrupción luego de cada tanda de conversiones
	CAPT_EnableInterrupts(CAPT, kCAPT_InterruptOfPollDoneEnable);
	NVIC_EnableIRQ(CMP_CAPT_IRQn);
	// Conversiones continuas
	CAPT_SetPollMode(CAPT, kCAPT_PollContinuousMode);
}

/**
 * @brief Wrapper que obtiene si el táctil se presionó o no
 */
bool wrapper_touch_is_touched(void) {
	// Lee el valor del contador del táctil
	capt_touch_data_t data;
	CAPT_GetTouchData(CAPT, &data);
	return data.count < 15;
}