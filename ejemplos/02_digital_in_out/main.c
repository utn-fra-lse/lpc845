#include "board.h"

// Puntero a GPIO, numero de puerto y pin del LED azul
#define LED_BLUE    GPIO, 1, 1
// Puntero a GPIO, numero de puerto y pin del pulsador de USER
#define USER_BTN    GPIO, 0, 4

/**
 * @brief Programa principal
 */
int main(void) {
    // Estructura de configuracion para salida
    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };
    // Estructura de configuracion para entrada
    gpio_pin_config_t in_config = { kGPIO_DigitalInput };
    // Habilito el puerto 0
    GPIO_PortInit(GPIO, 0);
    // Configuro el pin 4 como entrada
    GPIO_PinInit(USER_BTN, &in_config);
    // Habilito el clock del GPIO 1
    GPIO_PortInit(GPIO, 1);
    // Configuro el Pin 0 del GPIO 1 como salida
    GPIO_PinInit(LED_BLUE, &out_config);

    while(1) {

    	// Verifico el estado del pulsador (tiene pull-up)
    	if(!GPIO_PinRead(USER_BTN)) {
    		// Prendo el LED (anodo comun)
    		GPIO_PinWrite(LED_BLUE, 0);
    	}
    	else {
    		// Apago el LED
    		GPIO_PinWrite(LED_BLUE, 1);
    	}
    }
}