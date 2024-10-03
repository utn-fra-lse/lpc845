# lpc845

## Workspace

El directorio mencionado tiene ejemplos para el uso de perifericos del LPC845. Fue hecho con el MCUXpresso v11.9.1 y la version 2.15.0.

Ejemplos que van a encontrar en este directorio incluyen:

| Ejemplo | Descripcion |
| --- | --- |
| [01_blinky](ejemplos/01_blinky/) | Programa básico para compilar y ver un blinky
| [02_digital_in_out](ejemplos/02_digital_in_out/) | Ejemplo de uso de salidas y entradas digitales con los pulsadores 
| [03_systick_blinky](ejemplos/03_systick_blinky/) | Programa que hace un blinky coordinado por el Systick
| [04_adc_polling](ejemplos/04_adc_polling/) | Ejemplo de lectura analógica del potenciómetro por polling
| [05_adc_interrupt](ejemplos/05_adc_interrupt/) | Ejemplo de lectura analógica del potenciómetro por interrupción
| [06_usart_echo_polling](ejemplos/06_usart_echo_polling/) | Eco por USART por polling
| [07_usart_echo_interrupt](ejemplos/07_usart_echo_interrupt/) | Eco por USART por interrupción
| [08_i2c_master](ejemplos/08_i2c_master/) | Lectura de intensidad lumínica de un sensor por I2C
| [09_spi_master](ejemplos/09_spi_master/) | Lectura de temperatura de una termocupla tipo K con un MAX6675 a por SPI
| [10_timer](ejemplos/10_timer) | Blinkeo de LEDs por interrupción de Timer
| [11_sct_pwm](ejemplos/11_sct_pwm) | Control de PWM por consola para el LED azul
| [12_dac](ejemplos/12_dac) | Generacion de una triangular de 50 Hz con el DAC
| [13_iap](ejemplos/13_iap) | Grabado de una cadena de caracteres en la memoria Flash
| [15_freertos_blinky](ejemplos/15_freertos_blinky) | Conmutación de un LED con FreeRTOS
| [16_freertos_task_params](ejemplos/16_freertos_task_params) | Conmutación de dos LEDs a partir de la misma tarea diferenciada por parámetros
| [17_freertos_priority_change](ejemplos/17_freertos_priority_change) | Cambio de prioridad de tareas mediante handle
| [99_freertos_integrador](ejemplos/99_freertos_integrador) | Ejemplo integrador de un pequeño proyecto con FreeRTOS
