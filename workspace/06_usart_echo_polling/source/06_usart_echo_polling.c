#include <string.h>
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_swm.h"
#include "fsl_usart.h"


/*
 * @brief   Application entry point.
 */
int main(void) {
	// Inicializacion
    BOARD_BootClockFRO30M();
    BOARD_InitDebugConsole();

    // Habilito clock de matriz de conmutacion
    CLOCK_EnableClock(kCLOCK_Swm);
    // USART1_TXD connect to P0_25
    SWM_SetMovablePinSelect(SWM0, kSWM_USART1_TXD, kSWM_PortPin_P0_25);
    // USART1_RXD connect to P0_24
    SWM_SetMovablePinSelect(SWM0, kSWM_USART1_RXD, kSWM_PortPin_P0_24);
    // Deshabilito clock de matriz de conmutacion
    CLOCK_DisableClock(kCLOCK_Swm);

    CLOCK_Select(kUART1_Clk_From_MainClk);
	// Configuracion por defecto:
	// config->baudRate_Bps = 9600U;
	// config->parityMode = kUSART_ParityDisabled;
	// config->stopBitCount = kUSART_OneStopBit;
	// config->bitCountPerChar = kUSART_8BitsPerChar;
	// config->loopback = false;
	// config->enableRx = false;
	// config->enableTx = false;
	// config->syncMode = kUSART_SyncModeDisabled;
    usart_config_t usart_config;
    USART_GetDefaultConfig(&usart_config);
    // Cambio de la configuracion por defecto el baudrate y habilito pines de Tx y Rx
    usart_config.baudRate_Bps = 115200;
    usart_config.enableTx = true;
    usart_config.enableRx = true;
    // Habilito USART1
    USART_Init(USART1, &usart_config, CLOCK_GetFreq(kCLOCK_MainClk));

    PRINTF("Test de USART\n");

    while(1) {
    	// Variable para guardar el caracter
    	char str_in[64], str_out[64], nl;

    	PRINTF("Ingrese un texto y presione ENTER para enviar: ");

    	// Leo desde la consola
    	SCANF("%s", str_in);
    	// Leo el ENTER
    	SCANF("%c", &nl);

    	uint8_t i = 0;
    	do {
    		// Escribo por USART un byte
    		USART_WriteBlocking(USART1, (uint8_t*) &str_in[i], 1);
    		// Leo byte por USART
    		USART_ReadBlocking(USART1, (uint8_t*) &str_out[i++], 1);

    	} while(str_in[i] != '\0');

    	// Cierro la cadena
    	str_out[i] = 0;

    	PRINTF("Recibido desde USART: %s\n", str_out);

    }
    return 0 ;
}
