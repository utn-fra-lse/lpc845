#include "board.h"

// Puntero a GPIO, numero de puerto y pin
#define LED_BLUE    GPIO, 1, 1

/**
 * @brief Programa principal
 */
int main(void) {
    // Estructura de configuracion para salida
    gpio_pin_config_t config = { kGPIO_DigitalOutput, 1 };
    // Habilito el clock del GPIO 1
    GPIO_PortInit(GPIO, 1);
    // Configuro el pin 0 del GPIO 1 como salida
    GPIO_PinInit(LED_BLUE, &config);

    while(1) {
    	// Cambio el estado anterior del LED azul
    	GPIO_PinWrite(LED_BLUE, !GPIO_PinRead(LED_BLUE));
    	// Demora
    	for(uint32_t i = 0; i < 500000; i++);
    }
}
