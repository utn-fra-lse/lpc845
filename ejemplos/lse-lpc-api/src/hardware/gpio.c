#include "hardware/gpio.h"

// Funciones asignadas para cada GPIO
static gpio_function_t _gpio_functions[MAX_GPIO] = {0};

// Interrupciones asociadas a GPIO
static pint_pin_int_t _gpio_pint[MAX_GPIO] = {0};

// Interrupcion para asignar
static pint_pin_int_t _curr_pint = kPINT_PinInt0;

/**
 * @brief Asigna una funcion de las disponibles a un GPIO
 * @param gpio numero de GPIO para usar
 * @param func funcion a asignar dentro de las disponibles en gpio_function_t
 */
void gpio_set_function(uint32_t gpio, gpio_function_t func) {

	CLOCK_EnableClock(kCLOCK_Swm);
	SWM_SetMovablePinSelect(SWM0, func, gpio);
	CLOCK_DisableClock(kCLOCK_Swm);

	// Guardo la funcion en el array
	_gpio_functions[gpio] = func;
}

/**
 * @brief Obtiene la funcion asociada a un GPIO
 * @return funcion configurada en el GPIO
 */
gpio_function_t gpio_get_function(uint32_t gpio) {
	return _gpio_functions[gpio];
}

void gpio_set_irq_enabled_with_callback(uint32_t gpio, uint32_t event_mask, bool enabled, gpio_irq_callback_t callback) {
	// Asocio una interrupcion al GPIO
	_gpio_pint[gpio] = _curr_pint++;

	SYSCON_AttachSignal(SYSCON, _gpio_pint[gpio], gpio + (PINTSEL_ID << SYSCON_SHIFT));
	PINT_Init(PINT);
	PINT_PinInterruptConfig(PINT, _gpio_pint[gpio], event_mask, callback);
	PINT_EnableCallbackByIndex(PINT, _gpio_pint[gpio]);
}

pint_pin_int_t gpio_get_irq(uint32_t gpio) { 
	return _gpio_pint[gpio];
}

uint32_t gpio_get_from_irq(pint_pin_int_t pint) {
	for(uint32_t i = 0; i < MAX_GPIO; i++) {
		if(_gpio_pint[i] == pint) { return i; }
	}

	return MAX_GPIO;
}
