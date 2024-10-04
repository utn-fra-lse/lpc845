#include "board.h"

#include "FreeRTOS.h"
#include "task.h"

#include "fsl_debug_console.h"

// GPIO del LED azul
#define LED_BLUE	1

// Task Control Block de la tarea blink
StaticTask_t tcb_blink;
// Task Control Block de la tarea hello
StaticTask_t tcb_hello;

// Stack de la tarea blink
StackType_t stack_blink[configMINIMAL_STACK_SIZE];
// Stack de la tarea hello
StackType_t stack_hello[configMINIMAL_STACK_SIZE];


/**
 * @brief Tarea que hace parpadear el LED
 */
void task_blink(void *params) {

	while(1) {
		// Conmuto el LED
		GPIO_PinWrite(GPIO, 1, LED_BLUE, !GPIO_PinRead(GPIO, 1, LED_BLUE));
		// Bloqueo la tarea por medio segundo (500 ticks)
		vTaskDelay(500);
	}
}

/**
 * @brief Tarea que escribe mensaje en consola
 */
void task_hello(void *params) {

	while(1) {
		// Mensaje por consola
		PRINTF("Hola desde FreeRTOS!\r\n");
		// Bloqueo por 750 ticks
		vTaskDelay(750);
	}
}

/**
 * @brief Programa principal
 */
int main(void) {
	// Clock del sistema de 30 MHz
	BOARD_BootClockFRO30M();
	BOARD_InitDebugConsole();
	// Inicializo el puerto
	gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };
	GPIO_PortInit(GPIO, 1);
	GPIO_PinInit(GPIO, 1, LED_BLUE, &out_config);

	xTaskCreateStatic(
		task_blink,					// Callback de la tarea
		"Blinky",					// Nombre
		configMINIMAL_STACK_SIZE,	// Stack reservado
		NULL,						// Sin parametros
		tskIDLE_PRIORITY + 1UL,		// Prioridad
		stack_blink,				// Stack de la tarea
		&tcb_blink					// TCB de la tarea
	);

	xTaskCreateStatic(
		task_hello,					// Callback de la tarea
		"Hello",					// Nombre
		configMINIMAL_STACK_SIZE,	// Stack reservado
		NULL,						// Sin parametros
		tskIDLE_PRIORITY + 1UL,		// Prioridad
		stack_hello,				// Stack de la tarea
		&tcb_hello					// TCB de la tarea
	);

	vTaskStartScheduler();

    while(1);
    return 0;
}
