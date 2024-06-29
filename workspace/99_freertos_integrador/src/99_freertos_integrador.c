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

	xTaskCreate(
		task_init,
		"Init",
		tskINIT_STACK,
		NULL,
		tskINIT_PRIORITY,
		NULL
	);

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

	xTaskCreate(
		task_pwm,
		"PWM",
		tskPWM_STACK,
		NULL,
		tskPWM_PRIORITY,
		NULL
	);

	xTaskCreate(
		task_bh1750,
		"BH1750",
		tskBH1750_STACK,
		NULL,
		tskBH1750_PRIORITY,
		NULL
	);

	vTaskStartScheduler();

    while(1);
    return 0;
}
