#include "common/stdlib.h"
#include "hardware/gpio.h"

// Etiqueta para el LED azul
#define LED_BLUE	33

/*
 * @brief   Application entry point.
*/
int main(void) {
	// Inicializacion
	stdio_init_all();

	// Inicializacion de GPIO
	gpio_init(LED_BLUE);
	gpio_set_dir(LED_BLUE, true);

    while(1) {
    	// Cambio el estado anterior del LED azul
    	gpio_put(LED_BLUE, !gpio_get(LED_BLUE));
    	// Demora de 500 ms
    	sleep_ms(500);
    }
    return 0;
}

