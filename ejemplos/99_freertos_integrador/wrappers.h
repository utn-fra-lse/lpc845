#ifndef _WRAPPERS_H_
#define _WRAPPERS_H_

#include "board.h"
#include "fsl_power.h"
#include "fsl_swm.h"
#include "fsl_iocon.h"
#include "fsl_adc.h"
#include "fsl_sctimer.h"
#include "fsl_i2c.h"
#include "fsl_pint.h"
#include "fsl_capt.h"

#include "labels.h"

// Estructura para los GPIO
typedef struct {
	GPIO_Type *gpio;
	uint32_t port;
	uint32_t pin;
} gpio_t;

// Macro para facilitar el uso de la estructura gpio_t
#define GPIO_DESTRUCT(x)	x.gpio, x.port, x.pin

// Prototipos
void wrapper_adc_init(void);
void wrapper_btn_init(void);
void wrapper_gpio_enable_irq(gpio_t gpio, pint_pin_enable_t edge, pint_cb_t callback);
void wrapper_display_init(void);
void wrapper_display_write(uint8_t number);
void wrapper_pwm_init(void);
void wrapper_pwm_update_bled(int16_t duty);
void wrapper_pwm_update_rled(int16_t duty);
void wrapper_i2c_init(void);
void wrapper_bh1750_init(void);
float wrapper_bh1750_read(void);
void wrapper_touch_init(void);
bool wrapper_touch_is_touched(void);

// Funciones inline

/**
 * @brief Wrapper para inicializacion de puerto
 */
static inline void wrapper_gpio_init(uint8_t port) {
	GPIO_PortInit(GPIO, port);
}

/**
 * @brief Wrapper para obtener el valor de un boton
 * @param btn estructura a gpio del boton
 * @return estado del pin
 */
static inline bool wrapper_btn_get(gpio_t btn) {

	return (bool) GPIO_PinRead(GPIO_DESTRUCT(btn));
}

/**
 * @brief Wrapper para inicializar como salida un GPIO
 * @param led estructura de GPIO para la salida
 * @param default_output true para salida en high al habilitarlo
 */
static inline void wrapper_output_init(gpio_t led, bool default_output) {

	GPIO_PinInit(GPIO_DESTRUCT(led), &(gpio_pin_config_t){ kGPIO_DigitalOutput, default_output });
}

/**
 * @brief Wrapper para conseguir el valor del puerto de una estructura de GPIO
 * @param gpio estructura de GPIO
 * @return número de puerto
 */
static inline uint32_t wrapper_gpio_get_port(gpio_t gpio) {
	
	return gpio.port;
}

/**
 * @brief Wrapper para conseguir el valor del pin de una estructura de GPIO
 * @param gpio estructura de GPIO
 * @return número de pin
 */
static inline uint32_t wrapper_gpio_get_pin(gpio_t gpio) {

	return gpio.pin;
}

/**
 * @brief Wrapper para conmutar una salida
 * @param output estructura a GPIO de salida
 */
static inline void wrapper_output_toggle(gpio_t output) {
	// Leo el pin y se invierte
	GPIO_PortToggle(GPIO, wrapper_gpio_get_port(output), 1 << wrapper_gpio_get_pin(output));
}

/**
 * @brief Wrapper para apagar ambos displays
 */
static inline void wrapper_display_off(void) {
	// Pongo en uno ambos ánodos
	GPIO_PinWrite(COM_1, 1);
	GPIO_PinWrite(COM_2, 1);
}

/**
 * @brief Wrapper para prender el dígito del display
 * @param com estructura a pin conectado al comun del display
 */
static inline void wrapper_display_on(gpio_t com) {
	// Pongo un cero en el anodo
	GPIO_PinWrite(GPIO_DESTRUCT(com), 0);
}

/**
 * @brief Wrapper para prender ambos dígitos
 */
static inline void wrapper_display_on_both(void) {
	// Pongo un cero en ambos ánodos
	wrapper_display_on((gpio_t){COM_1});
	wrapper_display_on((gpio_t){COM_2});
}

/**
 * @brief Wrapper para apagar todos los segmentos
 */
static inline void wrapper_display_segments_off(void) {
	// Pongo un uno en cada segmento
	gpio_t pins[] = { {SEG_A}, {SEG_B}, {SEG_C}, {SEG_D}, {SEG_E}, {SEG_F}, {SEG_G} };
	for(uint8_t i = 0; i < sizeof(pins) / sizeof(gpio_t); i++) {
		GPIO_PinWrite(GPIO_DESTRUCT(pins[i]), 1);
	}
}

/**
 * @brief Wrapper para prender el segmento indicado
 * @param gpio estructura a gpio del segmento
 */
static inline void wrapper_display_segment_on(gpio_t gpio) {
	// Pongo un cero en el segmento indicado
	GPIO_PinWrite(GPIO_DESTRUCT(gpio), 0);
}

#endif