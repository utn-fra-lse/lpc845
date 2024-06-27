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

#define tskINIT_PRIORITY		(tskIDLE_PRIORITY + 2UL)
#define tskADC_READ_PRIORITY	(tskIDLE_PRIORITY + 1UL)

// Stacks para tareas

#define tskINIT_STACK			(configMINIMAL_STACK_SIZE)
#define tskADC_READ_STACK		(configMINIMAL_STACK_SIZE)

// Prototipos de funciones
void task_init(void *params);
void task_adc_read(void *params);

#endif
