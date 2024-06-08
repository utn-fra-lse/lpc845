# 06_usart_echo_polling

Se aprovecha la consola del MCUXpresso para tomar mensajes sencillos (y sin espacios) y reenviarlos por el TX de USART1.

El TX y RX del USART1 deben estar puenteados por un cable o jumper.

El mensaje enviado por USART1 en el pin de TX se recibe en el RX y se muestra por la consola.

El USART funciona por polling.

El mensaje va a escribirse y verse en la consola de MCUXpresso. Podemos abrir esta consola desde Window > Show View > Other y luego en General > Console.

## Pines usados

| Nombre | Pin |
| --- | --- |
| USART1 Tx | PIO0_24
| USART1 Rx | PIO0_25