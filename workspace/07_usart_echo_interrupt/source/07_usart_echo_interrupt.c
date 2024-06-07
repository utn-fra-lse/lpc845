#include <string.h>
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_swm.h"
#include "fsl_usart.h"

// Array para string
char str_rx[64];
// Indice para el array
uint8_t i = 0;
// Flag de recepcion por USART
bool usart_rx_done = true;

/*
 * @brief   Application entry point.
 */
int main(void) {
	// Cadena para mandar por USART
	char str_tx[64] = "Test de USART por interrupcion\n";
	// Indice para cadena
	uint8_t tx_index = 0;

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
    // Habilito interrupcion en USART y NVIC
    USART_EnableInterrupts(USART1, kUSART_RxReadyInterruptEnable);
    NVIC_EnableIRQ(USART1_IRQn);

    PRINTF("Test de USART por interrupcion\n");

    while(1) {


    	if(usart_rx_done) {
    		// Verifico si se termino de mandar la cadena
    		if(tx_index == sizeof(str_tx)) {
    			// Reinicio index
    			tx_index = 0;
    			// Muestro lo que se mando
    			PRINTF("Recibido por USART: %s", str_rx);
    		}

        	// Escribo por USART un byte
    		USART_WriteByte(USART1, (uint8_t) str_tx[tx_index++]);
    		// Bajo el flag
    		usart_rx_done = false;
    	}
    }
    return 0 ;
}


/**
 * @brief Handler para atender interrupciones de USART1
 */
void USART1_IRQHandler(void) {
	// Verifico que se haya disparado por RX
	if(USART_GetStatusFlags(USART1) & kUSART_RxReady) {
		// Leo el byte recibido
		str_rx[i++] = USART_ReadByte(USART1);
		// Aviso que se recibio el byte
		usart_rx_done = true;
	}
}

