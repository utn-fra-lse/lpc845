#include "wrappers.h"

// Variable privada para registrar el evento del PWM
static uint32_t pwm_led_event = 0;

/**
 * @brief Wrapper para inicializacion del ADC
 */
void wrapper_adc_init(void) {
    // Activo clock de matriz de conmutacion
    CLOCK_EnableClock(kCLOCK_Swm);
    // Configuro la funcion de ADC en el canal del LM35
//    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN7, true);
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
	uint32_t pins[] = { USR_BTN, ISP_BTN };
	for(uint8_t i = 0; i < sizeof(pins) / sizeof(uint32_t); i++) {
		GPIO_PinInit(GPIO, 0, pins[i], &config);
	}
}

/**
 * @brief Wrapper para inicializacion del display 7 segmentos
 */
void wrapper_display_init(void) {
	// Inicializo los pines como salidas
	gpio_pin_config_t config = { kGPIO_DigitalOutput, true };
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
	uint8_t values[] = { ~0x3f, ~0x6, ~0x5b, ~0x4f, ~0x66, ~0x6d, ~0x7d, ~0x7, ~0x7f, ~0x6f };
	// Array con los segmentos
	uint32_t pins[] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G };

	for(uint8_t i = 0; i < sizeof(pins) / sizeof(uint32_t); i++) {
		// Escribo el valor del bit en el segmento que corresponda
		uint32_t val = (values[number] & (1 << i))? 1 : 0;
		GPIO_PinWrite(GPIO, 0, pins[i], val);
	}
}

/**
 * @brief Wrapper para inicializacion del PWM para el LED
 */
void wrapper_pwm_init(void) {
	// Conecto la salida 4 del SCT al LED azul
    CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT4, kSWM_PortPin_P0_0 + LED);
    CLOCK_DisableClock(kCLOCK_Swm);

    // Eligo el clock para el Timer
    uint32_t sctimer_clock = CLOCK_GetFreq(kCLOCK_Fro);
    // Configuracion del SCT Timer
    sctimer_config_t sctimer_config;
    SCTIMER_GetDefaultConfig(&sctimer_config);
    SCTIMER_Init(SCT0, &sctimer_config);

    // Configuro el PWM
    sctimer_pwm_signal_param_t pwm_config = {
		.output = kSCTIMER_Out_4,		// Salida del Timer
		.level = kSCTIMER_HighTrue,		// Logica negativa
		.dutyCyclePercent = 0			// 50% de ancho de pulso
    };

    // Inicializo el PWM
    SCTIMER_SetupPwm(
		SCT0,
		&pwm_config,
		kSCTIMER_CenterAlignedPwm,
		1000,
		sctimer_clock,
		&pwm_led_event
	);
    // Inicializo el Timer
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);
}

/**
 * @brief Wrapper para actualizar el valor de duty del PWM
 */
void wrapper_pwm_update(int16_t duty) {
	// Verifico que no se haya excedido de los limites
	if(duty < 0) {
		duty = 0;
	}
	else if(duty > 100) {
		duty = 100;
	}
	// Actualizo el duty
	SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_4, duty, pwm_led_event);
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
    I2C_MasterInit(I2C1_BASE, &config, SystemCoreClock);
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
