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

// Estructura para datos de temperatura
typedef struct {
	float temp_lm35;
	float temp_ref;
} temp_data_t;

// Enum para indicar que se muestra en el display
typedef enum {
	kDISPLAY_TEMP,	// Se muestra la temperatura
	kDISPLAY_REF	// Se muestra la referencia
} display_variable_t;

// Prioridades de tareas

#define tskADC_READ_PRIORITY		(tskIDLE_PRIORITY + 1UL)
#define tskBTN_PRIORITY				(tskIDLE_PRIORITY + 1UL)
#define tskDISPLAY_WRITE_PRIORITY	(tskIDLE_PRIORITY + 1UL)
#define tskPWM_PRIORITY				(tskIDLE_PRIORITY + 1UL)

// Stacks para tareas

#define tskADC_READ_STACK		(configMINIMAL_STACK_SIZE)
#define tskBTN_STACK			(configMINIMAL_STACK_SIZE)
#define tskDISPLAY_WRITE_STACK	(configMINIMAL_STACK_SIZE)
#define tskPWM_STACK			(configMINIMAL_STACK_SIZE)


// Cola para datos del ADC
extern xQueueHandle queue_adc;
// Cola para eleccion de variable
extern xQueueHandle queue_display_variable;
// Cola para datos de temperatura
extern xQueueHandle queue_temp;

// Prototipos de funciones
void task_adc_read(void *params);
void task_btn(void *params);
void task_display_write(void *params);
void task_pwm(void *params);

#endif
