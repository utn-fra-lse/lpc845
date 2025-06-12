#include "board.h"
#include "fsl_ctimer.h"
#include "fsl_gpio.h"
#include "fsl_swm.h"

// GPIO para los LEDs
#define LED_GREEN	GPIO, 1, 0
#define LED_BLUE	GPIO, 0, 29

// Prototipos de callbacks para los eventos del CTimer
void ctimer_match_callback(uint32_t flags);

// Array para registrar los callbacks
ctimer_callback_t ctimer_callback_table[] = { ctimer_match_callback };

/**
 * @brief Programa principal
 */
int main(void) {
	// Configuracion de salida
    gpio_pin_config_t out_config_1 = {kGPIO_DigitalOutput, 1};
    gpio_pin_config_t out_config_2 = {kGPIO_DigitalOutput, 0};
    // Configuro los GPIO de los tres LEDs como salidas
    GPIO_PortInit(GPIO, 0);
    GPIO_PortInit(GPIO, 1);
    GPIO_PinInit(LED_GREEN, &out_config_1);
    GPIO_PinInit(LED_BLUE, &out_config_2);

    // Configuracion de CTimer
    ctimer_config_t config;
    CTIMER_StopTimer(CTIMER0);
    CTIMER_GetDefaultConfig(&config);
    CTIMER_Init(CTIMER0, &config);

    // Configuracion del canal 0
    ctimer_match_config_t match_config_0 = {
    	.matchValue = CLOCK_GetFreq(kCLOCK_CoreSysClk) / 4,	// Frecuencia de 4 Hz
    	.enableCounterReset = true,							// Se resetea el timer en match
		.enableCounterStop = false,							// El match no detiene el counter
		.outControl = kCTIMER_Output_Toggle,				// Cada match la salida conmuta
		.outPinInitState = false,							// Salida por defecto en low
		.enableInterrupt = true								// Habilito interrupcion
    };

    // Salida del CTimer Match 0 al LED verde
    CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetMovablePinSelect(SWM0, kSWM_T0_MAT_CHN0, kSWM_PortPin_P1_0);
    CLOCK_DisableClock(kCLOCK_Swm);

    // Habilito interrupcion en el NVIC
    NVIC_EnableIRQ(CTIMER0_IRQn);

    // Registro callback
    CTIMER_RegisterCallBack(CTIMER0, &ctimer_callback_table[0], kCTIMER_SingleCallback);
    CTIMER_SetupMatch(CTIMER0, kCTIMER_Match_0, &match_config_0);
    // Arranca el timer
    CTIMER_StartTimer(CTIMER0);

    while (1);
}

/**
 * @brief Callback para el march del CTimer
 */
void ctimer_match_callback(uint32_t flags) {
	// Contador
	static uint8_t i = 0;
	// Conmuto LED azul cada 2 interrupciones
	if(i++ % 2 == 0) {
		GPIO_PinWrite(LED_BLUE, !GPIO_PinRead(LED_BLUE));
	}
}
