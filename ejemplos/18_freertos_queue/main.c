#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_power.h"
#include "fsl_swm.h"
#include "fsl_adc.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/**
 * @brief Estructura para compartir por queue
 */
typedef struct {
    uint8_t channel;
    uint16_t res;
    float v;
} adc_t;

// Canal de ADC para el potenciómetro
#define RV21    0

// Cola de datos
QueueHandle_t queue;

/**
 * @brief Tarea que dispara el ADC
 */
void task_adc(void *params) {

    while(1) {
        // Disparo conversión
        adc_result_info_t info;
        ADC_DoSoftwareTriggerConvSeqA(ADC0);
        while(!ADC_GetChannelConversionResult(ADC0, RV22, &info));
        // Paso por la cola
        adc_t data = { .channel = info.channelNumber, .res = info.result, .v = 3.3 * info.result / 4095 };
        xQueueSend(queue, &data, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void task_print(void *params) {
    // Inicialización de la consola
    BOARD_InitDebugConsole();

    while(1) {
        // Leo de la cola
        adc_t data;
        xQueueReceive(queue, &data, portMAX_DELAY);
        // Muestro por consola
        PRINTF("El valor del canal %d es %d (%.2fV)\n", data.channel, data.res, data.v);
    }
}

/**
 * @brief Programa principal
 */
int main(void) {
    // Canal de ADC con matriz de conmutación
    CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN0, true);
    CLOCK_DisableClock(kCLOCK_Swm);

    // ADC con clock del FRO
    CLOCK_Select(kADC_Clk_From_Fro);
    CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1);

    // Prendo el ADC
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);
    // Calibracion del ADC
    ADC_DoSelfCalibration(ADC0, CLOCK_GetFreq(kCLOCK_Fro) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk));
    
    // Configuración del ADC
    adc_config_t adc_config;
    ADC_GetDefaultConfig(&adc_config);
    ADC_Init(ADC0, &adc_config);

    // Configuración de secuencia A
    adc_conv_seq_config_t adc_seq_config = {
        .channelMask = 1 << RV22,
        .triggerMask = 0,
        .interruptMode = kADC_InterruptForEachConversion
    };
    ADC_SetConvSeqAConfig(ADC0, &adc_seq_config);
    ADC_EnableConvSeqA(ADC0, true);

    // Inicialización de cola
    queue = xQueueCreate(1, sizeof(adc_t));

    // Creación de tareas
    xTaskCreate(task_adc, "", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(task_print, "", 2 * configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();
    while(1);
}
