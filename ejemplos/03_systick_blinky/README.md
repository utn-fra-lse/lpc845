# 03_systick_blinky

Ejemplo de blinky de un LED sincronizado por el SysTick del procesador.

## Pines usados

| Nombre | Pin |
| --- | --- |
| LED Blue | PIO1_1

## Configuración de SysTick

Se usó una frecuencia de clock del sistema de 24 MHz y se quiere lograr una frecuencia de 1 ms para la interrupción del SysTick.

$$
ticks = T_{SysTick} \times F_{CPU} = 1 ms \times 24 MHz = 24000
$$

Esto se traduce en la línea:

```c
SysTick_Config(SystemCoreClock / 1000);
```

Para lograr medio segundo de parpadeo, simplemente contamos 500 interrupciones de 1 ms.