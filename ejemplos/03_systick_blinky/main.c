#include "board.h"

// Puntero a GPIO, numero de puerto y pin del LED rojo
#define LED_RED     GPIO, 1, 2

/**
 * @brief Programa principal
 */
int main(void) {
    // Estructura de configuracion de salida
    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };
    // Habilito el puerto 1
    GPIO_PortInit(GPIO, 1);
    // Configuro LED como salida
    GPIO_PinInit(LED_RED, &out_config);

    // Configuro SysTick para 1 ms
    SysTick_Config(SystemCoreClock / 1000);

    while(1);
    return 0;
}

/**
 * @brief Handler para interrupcion de SysTick
 */
void SysTick_Handler(void) {
	// Variable para contar interrupciones
	static uint16_t i = 0;

	// Incremento contador
	i++;
	// Verifico si el SysTick se disparo 500 veces (medio segundo)
	if(i == 500) {
		// Reinicio el contador
		i = 0;
		// Conmuto el LED
		GPIO_PinWrite(LED_RED, !GPIO_PinRead(LED_RED));
	}
}