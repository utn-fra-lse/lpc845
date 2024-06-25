#include "board.h"
#include "fsl_sctimer.h"
#include "fsl_swm.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "fsl_swm.h"
#include "fsl_debug_console.h"

// Frecuencia de PWM
#define PWM_FREQ	1000

/**
 * @brief Programa principal
 */
int main(void) {
	// Inicializacion de consola
	BOARD_InitDebugConsole();

	// Conecto la salida 4 del SCT al LED azul
    CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT4, kSWM_PortPin_P1_1);
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
		.level = kSCTIMER_LowTrue,		// Logica negativa
		.dutyCyclePercent = 50			// 50% de ancho de pulso
    };

    // Variable para guardar el evento al quese asigna el PWM
    uint32_t event;
    // Inicializo el PWM
    SCTIMER_SetupPwm(
		SCT0,
		&pwm_config,
		kSCTIMER_CenterAlignedPwm,
		PWM_FREQ,
		sctimer_clock,
		&event
	);
    // Inicializo el Timer
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);

    while (1) {
    	// Variable para guardar el duty
    	uint32_t duty;
    	// Pido por consola un nuevo ancho de pulso
    	PRINTF("Ingrese un nuevo ciclo de actividad: ");
    	SCANF("%d", &duty);
    	// Verifico que este entre 0 y 100
    	if(duty < 100 && duty > 0){
    		// Actualizo el ancho de pulso
    		SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_4, duty, event);
    	}
    }
}
