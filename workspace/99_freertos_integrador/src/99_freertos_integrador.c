#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#include "app_tasks.h"

/**
 * @brief Programa principal
 */
int main(void) {
	// Clock del sistema a 30 MHz
	BOARD_BootClockFRO30M();

	// Configuro el ADC
	wrapper_adc_init();
	// Configuro el display
	wrapper_display_init();
	// Configuro botones
	wrapper_btn_init();

	// Inicializo colas
	queue_adc = xQueueCreate(1, sizeof(adc_data_t));
	queue_display_variable = xQueueCreate(1, sizeof(display_variable_t));

	// Tarea de lectura de ADC
	xTaskCreate(
		task_adc_read,
		"ADC",
		tskADC_READ_STACK,
		NULL,
		tskADC_READ_PRIORITY,
		NULL
	);

	xTaskCreate(
		task_btn,
		"Button",
		tskBTN_STACK,
		NULL,
		tskBTN_PRIORITY,
		NULL
	);

	xTaskCreate(
		task_display_write,
		"Write",
		tskDISPLAY_WRITE_STACK,
		NULL,
		tskDISPLAY_WRITE_PRIORITY,
		NULL
	);

	vTaskStartScheduler();

    while(1);
    return 0;
}
