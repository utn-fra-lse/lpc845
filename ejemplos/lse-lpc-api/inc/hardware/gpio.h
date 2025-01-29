#ifndef _LSE_GPIO_H_
#define _LSE_GPIO_H_

#ifdef __LPC84X__
#include "lpc845/LPC845.h"
#include "lpc845/fsl_gpio.h"
#include "lpc845/fsl_swm.h"
#include "lpc845/fsl_pint.h"
#include "lpc845/fsl_syscon.h"
#include "lpc845/fsl_pint.h"

// Macro para obtener el puerto de un pin determinado
#define PIN_TO_PORT(pin)	(pin > 31)? 1 : 0
// Macro para redefinir el nombre de las funciones de swm
#define gpio_function_t		swm_select_movable_t
// Macro para redefinir el nombre de las interrupciones
#define gpio_int_t			pint_pin_int_t

// Maxima cantidad de pines
#define MAX_GPIO		40

// Redefiniciones de los nombres de las funciones

#define GPIO_FUNC_I2C1_SDA		kSWM_I2C1_SDA
#define GPIO_FUNC_I2C1_SCL		kSWM_I2C1_SCL
#define GPIO_FUNC_I2C2_SDA		kSWM_I2C2_SDA
#define GPIO_FUNC_I2C2_SCL		kSWM_I2C2_SCL
#define GPIO_FUNC_I2C3_SDA		kSWM_I2C3_SDA
#define GPIO_FUNC_I2C3_SCL		kSWM_I2C3_SCL

#define GPIO_FUNC_PWM_OUT0		kSWM_SCT_OUT0
#define GPIO_FUNC_PWM_OUT1		kSWM_SCT_OUT1
#define GPIO_FUNC_PWM_OUT2		kSWM_SCT_OUT2
#define GPIO_FUNC_PWM_OUT3		kSWM_SCT_OUT3

// Defino el callback de la interrupcion por GPIO
typedef void(*gpio_irq_callback_t)(pint_pin_int_t gpio_irq, uint32_t event_mask);

#define GPIO_IRQ_LEVEL_LOW		kPINT_PinIntEnableLowLevel
#define GPIO_IRQ_LEVEL_HIGH		kPINT_PinIntEnableHighLevel
#define GPIO_IRQ_EDGE_FALL		kPINT_PinIntEnableFallEdge
#define GPIO_IRQ_EDGE_RISE		kPINT_PinIntEnableRiseEdge

#endif

// Prototipos

void gpio_set_function(uint32_t gpio, gpio_function_t func);
gpio_function_t gpio_get_function(uint32_t gpio);
void gpio_set_irq_enabled_with_callback(uint32_t gpio, uint32_t event_mask, bool enabled, gpio_irq_callback_t callback);
pint_pin_int_t gpio_get_irq(uint32_t gpio);
uint32_t gpio_get_from_irq(pint_pin_int_t pint);

/**
 * @brief Inicializa el puerto para el GPIO elegido
 * @param gpio numero de GPIO a usar
 */
static inline void gpio_init(uint32_t gpio) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(gpio);
	// Inicializo el puerto
	GPIO_PortInit(GPIO, port);
}

/**
 * @brief Configura una direccion para el GPIO
 * @param gpio numero de GPIO a configurar
 * @param direction true para salida, false para entrada
 */
static inline void gpio_set_dir(uint32_t gpio, bool direction) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(gpio);
	// Cambio el numero de GPIO si es del segundo puerto
	if(port) { gpio -= 32; }
	// Inicializa la direccion del gpio
	if(direction) { GPIO->DIR[port] |= (1UL << gpio); }
	else { GPIO->DIR[port] &= ~(1UL << gpio); }
}

/**
 * @brief Escribe un valor en una salida
 * @param gpio numero de GPIO a escribir
 * @param output valor para escribir
 */
static inline void gpio_put(uint32_t gpio, bool output) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(gpio);
	// Cambio el numero de GPIO si es del segundo puerto
	if(port) { gpio -= 32; }
	// Configura valor de salida
	GPIO_PinWrite(GPIO, port, gpio, output);
}

/**
 * @brief Lee el valor de un GPIO
 * @param gpio numero de GPIO a leer
 * @return estado del GPIO
 */
static inline bool gpio_get(uint32_t gpio) {
	// Veo el numero de puerto de acuerdo al GPIO
	uint32_t port = PIN_TO_PORT(gpio);
	// Cambio el numero de GPIO si es del segundo puerto
	if(port) { gpio -= 32; }
	// Configura valor de salida
	return (bool)GPIO_PinRead(GPIO, port, gpio);
}

#endif
