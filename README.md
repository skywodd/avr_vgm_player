# VGM Player project for AVR mcu
## by Fabien Batteix (alias SkyWodd)

---
### Overview 

**Work in progress**

This project is a VGM (Video Game Music) player based on a ATmega644/1284 AVR mcu.

This project used two sounds chip from the Megadrive game console :

* The SN76489 PSG sound chip (for noise and square waves)
* The YM2612 FM sound chip (for complex sounds emulation, like piano)

---
### Hardware

Basic

* ATmega644 or ATmega1284 mcu running at 16MHz
* FTDI basic module for Serial communication
* ICSP header for programmation
* 1x 23LC1023 SPI SRAM for VGM file storage

Human-computer interface

* 4x20 serial LCD from Sparkfun
* 3 leds (Yellow for RAM access, Red for "pause", Green for "playing")
* 3 buttons (disable/enable PSG sound chip, disable/enable FM sound chip, Play/Pause)

Audio

* 1x YM2612 FM sound chip
* 1x SN76489 PSG sound chip
* Analog front-end for mixing and speaker output

Dynamic clocking

* 2x LTC6903 (SPI version) for dynamic clocking of sound chips

---
### Software compatibility

* XMODEM (with CRC-16) for VGM file transfert over the serial link
* VGM 1.61 and earlier for music playback
* GD3 1.0 for track informations

For more informations please see:

* http://www.smspower.org/uploads/Music/vgmspec161.txt
* http://www.smspower.org/uploads/Music/gd3spec100.txt

---
### Test code for sound chips

Fake YM2612 and SN76489 are common on ebay.
To chek if your YM2612 or SN76489 are fake or not two test code are provided.
One for the YM2612 who play the same note again and again infinitly.
One for the SN76489 **Work in progress**