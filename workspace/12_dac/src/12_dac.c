#include "board.h"
#include "pin_mux.h"
#include "fsl_dac.h"
#include "fsl_swm.h"
#include "fsl_power.h"
#include "fsl_iocon.h"

/**
 * @brief Programa principal
 */
int main(void) {
	// Clock del sistema a 30 MHz
	BOARD_BootClockFRO30M();
	// Configuro la salida del DAC al P0 17
	CLOCK_EnableClock(kCLOCK_Swm);
	SWM_SetFixedPinSelect(SWM0, kSWM_DAC_OUT0, true);
	CLOCK_DisableClock(kCLOCK_Swm);

	// Habilito la funcion de DAC en el P0 17
	CLOCK_EnableClock(kCLOCK_Iocon);
	IOCON_PinMuxSet(IOCON, 0, IOCON_PIO_DACMODE_MASK);
	CLOCK_DisableClock(kCLOCK_Iocon);

	// Prendo el DAC
	POWER_DisablePD(kPDRUNCFG_PD_DAC0);

	// Configuro por defecto el DAC
	dac_config_t dac_config;
	DAC_GetDefaultConfig(&dac_config);
	DAC_Init(DAC0, &dac_config);
	DAC_SetBufferValue(DAC0, 0);

	// Configuro el Systick para 10 us
	SysTick_Config(SystemCoreClock / 100000);

    while(1);
    return 0;
}


/**
 * @brief Handler para la interrupcion del Systick
 */
void SysTick_Handler(void) {
	// Valor del DAC
	static uint16_t dac_value = 0;
	// Direccion de la rampa
	static bool dir_up = true;
	// Verico la direccion de la rampa
	if(dir_up) {
		dac_value++;
		// Veo si llegue al valor maximo
		if(dac_value == 1000) {
			// Cambio la direccion
			dir_up = false;
		}
	}
	else {
		dac_value--;
		// Veo si llegue al valor maximo
		if(dac_value == 0) {
			// Cambio la direccion
			dir_up = true;
		}
	}
	// Cargo el DAC
	DAC_SetBufferValue(DAC0, dac_value);
}
