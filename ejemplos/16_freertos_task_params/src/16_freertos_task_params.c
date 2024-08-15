#include "board.h"
#include "pin_mux.h"
#include "fsl_iocon.h"
#include "FreeRTOS.h"

#include "task.h"

/**
 * @brief Estructura de datos de LED
 */
typedef struct {
	uint32_t port;
	uint32_t pin;
} led_struct_t;

/**
 * @brief Estructura para pasar a la tarea
 */
typedef struct {
	led_struct_t led;
	uint32_t delay_ms;
} task_data_t;

/**
 * @brief Tarea template que parpadea LED
 */
void task_template(void *params) {
	// Obtengo la estructura del LED
	task_data_t *data = (task_data_t*) params;
	// Inicializo GPIO
    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };
    GPIO_PortInit(GPIO, data->led.port);
    GPIO_PinInit(GPIO, data->led.port, data->led.pin, &out_config);

	while(1) {
		// Conmuto el LED
		GPIO_PortToggle(GPIO, data->led.port, 1 << data->led.pin);
		// Delay
		vTaskDelay(data->delay_ms);
	}
}


/**
 * @brief Programa principal
 */
int main(void) {
	// Inicializo clocks
	BOARD_BootClockFRO30M();

	// Estructura de datos de LEDs
	led_struct_t led_green = { 1, 0 };
	led_struct_t led_blue = { 1, 1 };
	led_struct_t led_red = { 1, 2 };
	led_struct_t other_led_blue = { 0, 29 };

	// Estructuras para tareas
	task_data_t led_green_task = { led_green, 500 };
	task_data_t led_blue_task = { led_blue, 750 };
	task_data_t led_red_task = { led_red, 1000 };
	task_data_t other_led_blue_task = { other_led_blue, 1000 };

	xTaskCreate(
		task_template,
		"Other Blue",
		configMINIMAL_STACK_SIZE,
		(void*) &other_led_blue_task,
		tskIDLE_PRIORITY + 1,
		NULL
	);

	xTaskCreate(
		task_template,
		"Blue",
		configMINIMAL_STACK_SIZE,
		(void*) &led_blue_task,
		tskIDLE_PRIORITY + 1,
		NULL
	);


	// Inicio el Scheduler
	vTaskStartScheduler();

    while(1);
    return 0;
}
