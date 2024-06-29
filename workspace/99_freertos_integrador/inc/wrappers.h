#ifndef _WRAPPERS_H_
#define _WRAPPERS_H_

#include "board.h"
#include "fsl_power.h"
#include "fsl_swm.h"
#include "fsl_adc.h"
#include "fsl_sctimer.h"
#include "fsl_i2c.h"

#include "labels.h"

// Prototipos
void wrapper_adc_init(void);
void wrapper_btn_init(void);
void wrapper_display_init(void);
void wrapper_display_write(uint8_t number);
void wrapper_pwm_init(void);
void wrapper_pwm_update(int16_t duty);
void wrapper_i2c_init(void);
void wrapper_bh1750_init(void);
float wrapper_bh1750_read(void);

// Funciones inline

/**
 * @brief Wrapper para inicializacion de puerto
 */
static inline void wrapper_gpio_init(uint8_t port) {
	GPIO_PortInit(GPIO, port);
}

/**
 * @brief Obtiene el valor de un boton
 * @param btn el numero de pin del boton
 * @return estado del pin
 */
static inline bool wrapper_btn_get(uint32_t btn) {

	return (bool) GPIO_PinRead(GPIO, 0, btn);
}

/**
 * @brief Apaga ambos displays
 */
static inline void wrapper_display_off(void) {
	// Pongo en uno ambos anodos
	GPIO_PinWrite(GPIO, 0, COM_1, 1);
	GPIO_PinWrite(GPIO, 0, COM_2, 1);
}

/**
 * @brief Prende el digito del display
 * @param com pin conectado al comun del display
 */
static inline void wrapper_display_on(uint8_t com) {
	// Pongo un cero en el anodo
	GPIO_PinWrite(GPIO, 0, com, 0);
}

/**
 * @brief Apaga todos los segmentos
 */
static inline void wrapper_display_segments_off(void) {
	// Pongo un uno en cada segmento
	uint8_t pins[] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G };
	for(uint8_t i = 0; i < sizeof(pins) / sizeof(uint8_t); i++) {
		GPIO_PinWrite(GPIO, 0, pins[i], 1);
	}
}

/**
 * @brief Prende el segmento indicado
 * @param segment numero de pin del segmento
 */
static inline void wrapper_display_segment_on(uint8_t segment) {
	// Pongo un cero en el segmento indicado
	GPIO_PinWrite(GPIO, 0, segment, 0);
}

#endif
