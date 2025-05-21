Hardware requirements
=====================
- Micro USB cable
- LPC845 Breakout board
- Personal Computer

Board settings
==============
- ADC CH0 input signal 32(PIO0-7).

Prepare the demo
================
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port on the board.
2.  Open a serial terminal with the following settings:
    - 9600 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
Adjust the potentiometer and press any key from keyboard to trigger the conversion.
The log below shows the output of the ADC dma driver example in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ADC DMA example.
ADC Calibration Done.
Configuration Done.
Type in any key to trigger the conversion ...
Conversion word : 0x80025F30
Conversion value: 1523

Conversion word : 0x80025F30
Conversion value: 1523

Conversion word : 0x80025F30
Conversion value: 1522

...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
