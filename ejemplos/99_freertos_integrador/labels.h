#ifndef _LABELS_H_
#define _LABELS_H_

// Canal del ADC para el potenciometro
#define REF_POT_CH	8
// Canal del ADC para el LM35
#define LM35_CH		  0
// Pin para el LED adicional
#define LED			    GPIO, 0, 29
// Pin para el LED azul
#define BLED        GPIO, 1, 1
// Pin para el LED verde
#define GLED        GPIO, 1, 2

// Etiquetas para los pines del 7 segmentos

#define SEG_A	GPIO, 0, 10
#define SEG_B	GPIO, 0, 11
#define SEG_C	GPIO, 0, 6
#define SEG_D	GPIO, 0, 14
#define SEG_E	GPIO, 0, 0
#define SEG_F	GPIO, 0, 13
#define SEG_G	GPIO, 0, 15
#define COM_1	GPIO, 0, 8
#define COM_2	GPIO, 0, 9

// Etiquetas de botones

#define USR_BTN		GPIO, 0, 4
#define ISP_BTN		GPIO, 0, 12
#define S1_BTN		GPIO, 0, 16
#define S2_BTN		GPIO, 0, 25

// Etiqueta del buzzer
#define BUZZER    GPIO, 0, 28

// Etiqueta del infrarojo (entrada)
#define CNY70     GPIO, 0, 19
// Etiqueta del infrarojo (enable)
#define CNY70_EN  GPIO, 0, 17

// Direccion del sensor de luz
#define BH1750_ADDR	0x5C


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

#endif