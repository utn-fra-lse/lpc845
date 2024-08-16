#include "board.h"
#include "FreeRTOS.h"
#include "fsl_debug_console.h"
#include "fsl_swm.h"
#include "fsl_power.h"
#include "fsl_adc.h"

#include "task.h"

// Etiquetas

// Pin de boton de user
#define USR_BTN		4
// ADC de RV21
#define RV21		0
// ADC de RV22
#define RV22		8

// Handle para tareas de secuencias
TaskHandle_t seq_a_handle = NULL, seq_b_handle = NULL;

/**
 * @brief Tarea de inicializacion
 * @param params puntero a datos
 */
void task_init(void *params) {
	// Inicializo boton de USER
	GPIO_PortInit(GPIO, 0);
	gpio_pin_config_t input = { kGPIO_DigitalInput };
	GPIO_PinInit(GPIO, 0, USR_BTN, &input);

	// Inicializacion de ADC

    // Activo clock de matriz de conmutacion
    CLOCK_EnableClock(kCLOCK_Swm);
    // Configuro la funcion de ADC en el canal del RV21 y RV22
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN0, true);
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN8, true);
    // Desactivo clock de matriz de conmutacion
    CLOCK_DisableClock(kCLOCK_Swm);

    // Elijo clock desde el FRO con divisor de 1 (30MHz)
    CLOCK_Select(kADC_Clk_From_Fro);
    CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1);

    // Prendo el ADC
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);

    // Obtengo frecuencia deseada y calibro ADC
	uint32_t frequency = CLOCK_GetFreq(kCLOCK_Fro) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk);
	ADC_DoSelfCalibration(ADC0, frequency);
	// Configuracion por defecto del ADC
	adc_config_t adc_config;
	ADC_GetDefaultConfig(&adc_config);
    // Habilito el ADC
	ADC_Init(ADC0, &adc_config);
	// Configuracion para la conversion para secuencia A
	adc_conv_seq_config_t adc_sequence = {
		.channelMask = 1 << RV21,								// Canal del RV21
		.triggerMask = 0,										// No hay trigger por hardware
		.triggerPolarity = kADC_TriggerPolarityPositiveEdge,	// Flanco ascendente
		.enableSyncBypass = false,								// Sin bypass de trigger
		.interruptMode = kADC_InterruptForEachConversion		// Interrupciones para cada conversion
	};
	ADC_SetConvSeqAConfig(ADC0, &adc_sequence);
	// Conversion para secuencia B
	adc_sequence.channelMask = 1 << RV22;		// Canal del RV22
	ADC_SetConvSeqBConfig(ADC0, &adc_sequence);
	// Habilito secuencias
	ADC_EnableConvSeqA(ADC0, true);
	ADC_EnableConvSeqB(ADC0, true);

	// Elimino tarea
	vTaskDelete(NULL);
}

/**
 * @brief Tarea de boton de user
 * @param params puntero a datos
 */
void task_user(void *params) {

	while(1) {
		// Verifico si se apreto el boton
		if(!GPIO_PinRead(GPIO, 0, USR_BTN)) {
			// Obtengo las prioridades de las tareas
			UBaseType_t seq_a_priority = uxTaskPriorityGet(seq_a_handle);
			UBaseType_t seq_b_priority = uxTaskPriorityGet(seq_b_handle);
			// Invierto las prioridades
			vTaskPrioritySet(seq_a_handle, seq_b_priority);
			vTaskPrioritySet(seq_b_handle, seq_a_priority);
		}
	}
}

/**
 * @brief Tarea de ADC con secuencia A
 * @param params puntero a datos
 */
void task_adc_seq_a(void *params) {
	// Resultado de conversion
	adc_result_info_t adc_info;

	while(1) {
		// Arranco una nueva conversion
		ADC_DoSoftwareTriggerConvSeqA(ADC0);
    	// Espero a terminar la conversion
    	while(!ADC_GetChannelConversionResult(ADC0, RV21, &adc_info));
    	// Muestro resultado
    	PRINTF(
			"El resultado del canal %ld en el PIO0_7 (RV21) dio %d\n",
			adc_info.channelNumber,
			adc_info.result
    	);
    	// Bloqueo por un tiempo
    	vTaskDelay(500);
	}
}

/**
 * @brief Tarea de ADC con secuencia B
 * @param params puntero a datos
 */
void task_adc_seq_b(void *params) {
	// Resultado de conversion
	adc_result_info_t adc_info;

	while(1) {
		// Arranco una nueva conversion
		ADC_DoSoftwareTriggerConvSeqB(ADC0);
    	// Espero a terminar la conversion
    	while(!ADC_GetChannelConversionResult(ADC0, RV22, &adc_info));
    	// Muestro resultado
    	PRINTF(
			"El resultado del canal %ld en el PIO0_18 (RV22) dio %d\n",
			adc_info.channelNumber,
			adc_info.result
    	);
    	// Bloqueo por un tiempo
    	vTaskDelay(500);
	}
}


/**
 * @brief Programa principal
 */
int main(void) {
	// Inicializacion de clock y consola
	BOARD_BootClockFRO30M();
    BOARD_InitDebugConsole();

    // Creo tareas

    xTaskCreate(
		task_init,
		"Init",
		2 * configMINIMAL_STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY + 2,
		NULL
	);

    xTaskCreate(
    	task_user,
		"User",
		configMINIMAL_STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY + 1,
		NULL
    );

    xTaskCreate(
		task_adc_seq_a,
		"SEQ A",
		2 * configMINIMAL_STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY + 1,
		&seq_a_handle
    );

    xTaskCreate(
		task_adc_seq_b,
		"SEQ B",
		2 * configMINIMAL_STACK_SIZE,
		NULL,
		tskIDLE_PRIORITY,
		&seq_b_handle
    );

    // Arranco scheduler
    vTaskStartScheduler();

    while(1);
    return 0;
}
