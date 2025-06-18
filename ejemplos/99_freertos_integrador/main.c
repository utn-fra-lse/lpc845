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

	// Creacion de tareas

	xTaskCreate(task_init, "Init", tskINIT_STACK, NULL, tskINIT_PRIORITY, NULL);
	xTaskCreate(task_adc, "ADC", tskADC_STACK, NULL, tskADC_PRIORITY, NULL);
	xTaskCreate(task_display_change, "Button", tskDISPLAY_CHANGE_STACK, NULL, tskDISPLAY_CHANGE_PRIORITY, NULL);
	xTaskCreate(task_control, "Write", tskCONTROL_STACK, NULL, tskCONTROL_PRIORITY, NULL);
	xTaskCreate(task_display, "Display", tskDISPLAY_STACK, NULL, tskDISPLAY_PRIORITY, &handle_display);
	xTaskCreate(task_pwm, "PWM", tskPWM_STACK, NULL, tskPWM_PRIORITY, NULL);
	xTaskCreate(task_bh1750, "BH1750", tskBH1750_STACK, NULL, tskBH1750_PRIORITY, NULL);
	xTaskCreate(task_animation, "Animation", tskANIMATION_STACK, NULL, tskANIMATION_PRIORITY, NULL);
	xTaskCreate(task_blinky, "Blinky LED", tskBLINKY_STACK, NULL, tskBLINKY_PRIORITY, NULL);
	xTaskCreate(task_buzzer, "Buzzer", tskBUZZER_STACK, NULL, tskBUZZER_PRIORITY, NULL);
	xTaskCreate(task_counter, "Counter", tskCOUNTER_STACK, NULL, tskCOUNTER_PRIORITY, NULL);
	xTaskCreate(task_counter_btns, "Counter Btns", tskCOUNTER_BTNS_STACK, NULL,tskCOUNTER_BTNS_PRIORITY, NULL);

	vTaskStartScheduler();
}