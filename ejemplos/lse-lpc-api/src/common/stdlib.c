#include "common/stdlib.h"

// Variable para controlar el bloqueo del sleep
static bool sleep_done = false;
// Cantidad de interrupciones de Systick
static uint32_t max_ticks = 0;

/**
 * @brief Demora en milisegundos
 * @param ms cantidad de milisegundos
 */
void sleep_ms(uint32_t ms) {
	// Booleano para bloquear
	sleep_done = false;
	// Configuro Systick para 1 ms
	SysTick_Config(SystemCoreClock / 1000);
	// Seteo cuantos ms tienen que pasar
	max_ticks = ms;
	// Habilito interrupcion
	NVIC_EnableIRQ(SysTick_IRQn);
	// Espero a que termine el delay
	while(!sleep_done);
	// Deshabilito interrupcion
	NVIC_DisableIRQ(SysTick_IRQn);
}

/**
 * @brief Handler para la interrupcion de Systick
 */
void SysTick_Handler(void) {
	// Cantidad de interrupciones
	static uint32_t systick_count = 0;
	// Verifico si se cumplio el tiempo
	if(systick_count++ == max_ticks) {
		// Reinicio contador y booleano
		sleep_done = true;
		systick_count = 0;
	}
}
