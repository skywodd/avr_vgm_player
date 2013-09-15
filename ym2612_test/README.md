# AVR test code for YM2612
## by Fabien Batteix

---
### Overview

This program is a simple test code for the YM2612 FM sound chip using an AVR ATmega328p mcu.
This program configure the YM2612 to sound like a "grand piano" and play note on / note off in loop.

* For more informations about wiring please see: http://en.wikipedia.org/wiki/Yamaha_YM2612
* For more informations about YM2612 registers please see: http://www.smspower.org/maxim/Documents/YM2612

---
### Remarks

* This test code is heavly based on Furrtek's YM2612 test code. Big thanks Furrtek for the help !
* This test code is made to run on an ATmega328/ATmega168 mcu with a 16MHz external crystal.
 
---
### Pinmap (Arduino UNO compatible)

| YM2612 pin | ATmega328/168 pin | Arduino UNO pin |
|:----------:|:-----------------:|:---------------:|
| IC         | PC5               | A5              |
| CS         | PC4               | A4              |
| WR         | PC3               | A3              |
| A0         | PC1               | A1              |
| RD         | PC2               | A2              |
| A1         | PC0               | A0              |
| D0~D7      | Whole PORT D      | D0 to D7        |
| MCLOCK     | PB1 = OC1A        | pin D9          |

**BIG WARNING FOR ARDUINO USERS**

Normally ICSP port is used to program the AVR chip (see the makefile for details). 
So, if you use an arduino UNO board to run this test code BE VERY CAREFULL.
If you don't known what you make you will be in trouble.

To avoid problems you can compile and upload this code using the Arduino IDE BUT you will need to disconnect pins Rx/Tx before upload !