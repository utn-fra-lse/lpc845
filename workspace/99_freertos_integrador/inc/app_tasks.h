#ifndef _APP_TASKS_H_
#define _APP_TASKS_H_

#include "board.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "wrappers.h"

// Estructura para datos del ADC
typedef struct {
	uint16_t temp_raw;
	uint16_t ref_raw;
} adc_data_t;

// Prioridades de tareas

#define tskADC_READ_PRIORITY		(tskIDLE_PRIORITY + 1UL)
#define tskDISPLAY_WRITE_PRIORITY	(tskIDLE_PRIORITY + 1UL)

// Stacks para tareas

#define tskADC_READ_STACK		(configMINIMAL_STACK_SIZE)
#define tskDISPLAY_WRITE_STACK	(configMINIMAL_STACK_SIZE)


// Cola para datos del ADC
extern xQueueHandle queue_adc;

// Prototipos de funciones
void task_adc_read(void *params);
void task_display_write(void *params);

#endif
