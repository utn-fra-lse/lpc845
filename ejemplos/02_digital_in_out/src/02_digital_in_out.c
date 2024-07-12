#include "board.h"
#include "LPC845.h"

// Etiqueta para el pulsador USER
#define USER_BTN	4
// Etiqueta para el LED azul
#define LED_BLUE	1

/*
 * @brief   Application entry point.
*/
int main(void) {

	// Inicializacion
    BOARD_InitBootClocks();

    // Estructura de configuracion para salida
    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };
    // Estructura de configuracion para entrada
    gpio_pin_config_t in_config = { kGPIO_DigitalInput };
    // Habilito el puerto 0
    GPIO_PortInit(GPIO, 0);
    // Configuro el pin 4 como entrada
    GPIO_PinInit(GPIO, 0, USER_BTN, &in_config);
    // Habilito el clock del GPIO 1
    GPIO_PortInit(GPIO, 1);
    // Configuro el Pin 0 del GPIO 1 como salida
    GPIO_PinInit(GPIO, 1, LED_BLUE, &out_config);

    while(1) {

    	// Verifico el estado del pulsador (tiene pull-up)
    	if(!GPIO_PinRead(GPIO, 0, USER_BTN)) {
    		// Prendo el LED (anodo comun)
    		GPIO_PinWrite(GPIO, 1, LED_BLUE, 0);
    	}
    	else {
    		// Apago el LED
    		GPIO_PinWrite(GPIO, 1, LED_BLUE, 1);
    	}
    }

    return 0;
}
