## @brief Generic makefile for AVR MCU 
## @author Fabien Batteix (alias SkyWodd)
## @version 1.0
## @link http://skyduino.wordpress.com/
##
## Please report bug to <skywodd at gmail.com>
##
## @section licence_sec License
##  This program is free software: you can redistribute it and/or modify\n
##  it under the terms of the GNU General Public License as published by\n
##  the Free Software Foundation, either version 3 of the License, or\n
##  (at your option) any later version.\n
## \n
##  This program is distributed in the hope that it will be useful,\n
##  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
##  GNU General Public License for more details.\n
## \n
##  You should have received a copy of the GNU General Public License\n
##  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n

# AVR mcu target, should not be changed
TARGET ?= atmega328p

# System clock frequency
F_CPU ?= 16000000

# AVR mcu fuses
#LFUSE = 0xf7
#HFUSE = 0xd9
#EFUSE = 0xff
#LOCKFUSE = 0x0f

# Source files to compile
SOURCES = ym2612_test.c

# Output project name
OUTPUT = ym2612Test

# Programmer name
AVRDUDE_PROGRAMMER ?= usbtiny

# Compilator switch
CCFLAGS += -Wall -Os -ffunction-sections
LDFLAGS += -Wl,-gc-sections

# Source file dependencies

# ----- Nothing to change after this line
OBJECTS =  $(SOURCES:.c=.o)
COMPILER = avr-gcc -mmcu=$(TARGET) -std=gnu99 -DF_CPU=$(F_CPU)UL $(EXTRA)
OBJCOPY = avr-objcopy -O ihex
OBJSIZE = avr-size -C --mcu=$(TARGET)
AVRDUDE_ICSP = avrdude -p $(TARGET) -c $(AVRDUDE_PROGRAMMER)

all: elf hex size

%.o: %.c
	$(COMPILER) -c $< -o $@ $(CCFLAGS)
	
elf: $(OBJECTS)
	$(COMPILER) -o $(OUTPUT).elf $(LDFLAGS) $^
	
hex: $(OUTPUT).elf
	$(OBJCOPY) $(OUTPUT).elf $(OUTPUT).hex
	
size: $(OUTPUT).elf
	$(OBJSIZE) $(OUTPUT).elf

flash: $(OUTPUT).hex
	$(AVRDUDE_ICSP) -U flash:w:$(OUTPUT).hex
	
#fuses:
#	$(AVRDUDE_ICSP) -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m  -U lock:w:$(LOCKFUSE):m
	
clean:
	rm -f $(OBJECTS) $(OUTPUT).elf $(OUTPUT).hex