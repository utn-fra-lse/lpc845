#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "fsl_iap.h"
#include "fsl_debug_console.h"

// Mumero de sector a usar
#define SECTOR	20
// Direccion de la Flash a escribir
#define FLASH_ADDR	0x00005000
// Maima capacidad del buffer
#define MAX_SIZE	256

// Buffer para guardar los datos de la Flash
uint8_t buf[MAX_SIZE] = "Solo porque no me importe no significa que no entienda";

/**
 * @brief Programa principal
 */
int main(void) {
	// Uso 30 MHz de clock
	BOARD_BootClockFRO30M();
	// Inicializacion de la consola
    BOARD_InitDebugConsole();

    PRINTF("Borrado de Memoria Flash\n");
    // Verifico que el sector pueda escribirse
    if(IAP_PrepareSectorForWrite(SECTOR, SECTOR + 1) != kStatus_IAP_Success){
    	PRINTF("ERROR IAP_PrepareSectorForWrite\n");
    	while(1);
    }
    // Borro el sector preparado
    if(IAP_EraseSector(SECTOR, SECTOR + 1, SystemCoreClock) != kStatus_IAP_Success){
    	PRINTF("ERROR IAP_EraseSector \n");
    	while(1);
    }

    PRINTF("Escritura de Memoria Flash\n");
    // Verifico que el sector pueda escribirse
    if(IAP_PrepareSectorForWrite(SECTOR, SECTOR + 1) != kStatus_IAP_Success){
    	PRINTF("ERROR IAP_PrepareSectorForWrite\n");
    	while(1);
    }
    // Escribo el array de RAM en Flash
    if(IAP_CopyRamToFlash(FLASH_ADDR, (uint32_t*)buf, MAX_SIZE, SystemCoreClock) != kStatus_IAP_Success){
    	PRINTF("ERROR IAP_CopyRamToFlash\n");
    	while(1);
    }

    PRINTF("Escritura terminada!\n");

    while(1);
}
