#include "board.h"

#include "FreeRTOS.h"
#include "task.h"

// Puntero a GPIO, numero de puerto y pin de LED verde
#define LED_GREEN   GPIO, 1, 0

/**
 * @brief Tarea que hace parpadear el LED
 */
void task_blink(void *params) {

	while(1) {
		// Conmuto el LED
		GPIO_PinWrite(LED_GREEN, !GPIO_PinRead(LED_GREEN));
		// Bloqueo la tarea por medio segundo (500 ticks)
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

/**
 * @brief Programa principal
 */
int main(void) {
	// Inicializo el puerto
	gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };
	GPIO_PortInit(GPIO, 1);
	GPIO_PinInit(LED_GREEN, &out_config);

	xTaskCreate(
		task_blink,					// Callback de la tarea
		"Blinky",					// Nombre
		configMINIMAL_STACK_SIZE,	// Stack reservado
		NULL,						// Sin parametros
		tskIDLE_PRIORITY + 1UL,		// Prioridad
		NULL						// Sin handler
	);

    // Arranca el Scheduler de FreeRTOS
	vTaskStartScheduler();
    while(1);
    return 0;
}