# AVR test code for SN76489
## by Fabien Batteix (alias SkyWodd)

---
### Overview

This program is a simple test code for the SN76489 PSG sound chip using an AVR ATmega328p mcu.
This program configure the SN76489 to play notes: SOL, LA, SI and noise in loop for 1 second each.

* For more informations about wiring please see: http://members.casema.nl/hhaydn/howel/parts/76489.htm (remark: THE Fn bits are INVERTED, so you should read F0=F9, F1=F8, ...)
* For more informations about SN76489 registers please see: http://www.smspower.org/Development/SN76489 (remark: Fn bits are OK in this one)

---
### Remarks

* This test code is made to run on an ATmega328/ATmega168 mcu with a 16MHz external crystal.
 
---
### Pinmap (Arduino UNO compatible)

| SN76489 pin | ATmega328/168 pin | Arduino UNO pin |
|:-----------:|:-----------------:|:---------------:|
| READY       | PC5               | A5              |
| WE          | PC4               | A4              |
| CE          | PC3               | A3              |
| D0~D7       | Whole PORT D      | D0 to D7        |
| CLOCK       | PB1 = OC1A        | D9              |

**BIG WARNING FOR ARDUINO USERS**

Normally ICSP port is used to program the AVR chip (see the makefile for details). 
So, if you use an arduino UNO board to run this test code BE VERY CAREFULL.
If you don't known what you make you will be in trouble.

To avoid problems you can compile and upload this code using the Arduino IDE BUT you will need to disconnect pins Rx/Tx before upload !