/**
 * SN76489 test code for AVR.
 * 
 * This program is a simple test code for the SN76489 PSG sound chip using an AVR ATmega328p mcu.
 * For more informations about wiring please see: http://members.casema.nl/hhaydn/howel/parts/76489.htm
 * For more informations about SN76489 registers please see: http://www.smspower.org/Development/SN76489
 *
 * @warning This test code is made to run on an ATmega328/ATmega168 mcu with a 16MHz external crystal.
 * 
 * @author Fabien Batteix <skywodd@gmail.com>
 * @link http://skyduino.wordpress.com My Blog about electronics
 */

/* Dependencies */
#include <avr/io.h>     // For I/O and other AVR registers
#include <util/delay.h> // For timing

/* Pinmap (Arduino UNO compatible) */
#define PSG_READY (5)       // PC5 (= pin A5 for Arduino UNO)
#define PSG_WE (4)          // PC4 (= pin A4 for Arduino UNO)
#define PSG_CE (3)          // PC3 (= pin A3 for Arduino UNO)
#define PSG_CTRL_DDR DDRC
#define PSG_CTRL_PORT PORTC
#define PSG_CTRL_PIN PINC
#define PSG_DATA_DDR DDRD
#define PSG_DATA_PORT PORTD // Whole PORT D for data bus (= pins D0 to D7 for Arduino UNO)
#define PSG_CLOCK (1)       // PB1 = OC1A (= pin D9 for Arduino UNO)
#define PSG_CLOCK_DDR DDRB

/* ----- BIG WARNING FOR ARDUINO USERS -----
 * Normally ICSP port is used to program the AVR chip (see the makefile for details). 
 * So, if you use an arduino UNO board to run this test code BE VERY CAREFULL.
 * If you don't known what you make you will be in trouble.
 *
 * To avoid problems you can compile and upload this code using the Arduino IDE BUT you will need to disconnect pins Rx/Tx before upload !
 */

/** Macro for frequency register */
#define FREG_REG_VAL(f) (4000000UL / 32 / (f))

/* Register values */
#define ATTENUATION_2DB (1)
#define ATTENUATION_4DB (2)
#define ATTENUATION_8DB (4)
#define ATTENUATION_16DB (8)
#define ATTENUATION_OFF (15)

/* Noise controls */
#define NOISE_PERIODIC_FEEDBACK (0)
#define NOISE_WHITE_FEEDBACK (1 << 2)
#define NOISE_SHIFT_512 (0)
#define NOISE_SHIFT_1024 (1)
#define NOISE_SHIFT_2048 (2)
#define NOISE_SHIFT_TONE3 (3)

/**
 * Send raw data to the SN76489
 * 
 * @param data Data to write
 */
static void write_psg(uint8_t data) {
	//while(PSG_CTRL_PIN & _BV(PSG_READY)); // Wait for chip to be ready
	PSG_DATA_PORT = data;
	_delay_us(500);
	PSG_CTRL_PORT &= ~_BV(PSG_CE); // CS LOW
	_delay_us(500);
	PSG_CTRL_PORT &= ~_BV(PSG_WE); // Write data
	_delay_us(500);
	PSG_CTRL_PORT |= _BV(PSG_CE); // CS HIGH
	_delay_us(500);
	PSG_CTRL_PORT |= _BV(PSG_WE);
	_delay_us(500);
}

/**
 * Set the value of a channel (with latch)
 *
 * @param reg Register address
 * @param data Data to write
 */
static void setreg(uint8_t reg, uint8_t data) {
	write_psg(0x80 | ((reg & 0x07) << 4) | (data & 0x0F));
}


/**
 * Set the frequency of a channel
 *
 * @param channel Channel number (0, 1, 2)
 * @param frequency Frequency in Hz
 */
static void setFrequency(uint8_t channel, uint16_t frequency) {
	uint16_t f = FREG_REG_VAL(frequency);
	setreg(2 * channel, f & 0x0F);
	write_psg((f >> 4) & 0x3F);
}

/** Program entry point */
int main(void) {

	/* Pins setup */
	PSG_CTRL_DDR |= _BV(PSG_WE) | _BV(PSG_CE);
	PSG_CTRL_DDR &= ~_BV(PSG_READY);
	PSG_DATA_DDR = 0xFF;
	PSG_CLOCK_DDR |= _BV(PSG_CLOCK);
	PSG_CTRL_PORT |= _BV(PSG_WE) | _BV(PSG_CE) | _BV(PSG_READY); /* CE and WE HIGH by default + Pull-up on READY */
	
	/* F_CPU / 4 clock generation */
	TCCR1A = _BV(COM1A0);            /* Toggle OCA1 on compare match */
	TCCR1B = _BV(WGM12) | _BV(CS10); /* CTC mode with prescaler /1 */
	TCCR1C = 0;                      /* Flag reset */
	TCNT1 = 0;                       /* Counter reset */
	OCR1A = 1;                       /* Divide base clock by 4 */
	
	/* SN76489 Test code */ 
	setFrequency(0, 392); // Sol
	_delay_ms(100);
	setreg(0x01, ATTENUATION_OFF);
	_delay_ms(100);
	setFrequency(1, 440); // La 
	_delay_ms(100);
	setreg(0x03, ATTENUATION_OFF);
	_delay_ms(100);
	setFrequency(2, 493); // Si
	_delay_ms(100);
	setreg(0x05, ATTENUATION_OFF);
	_delay_ms(100);
	setreg(0x06, NOISE_WHITE_FEEDBACK | NOISE_SHIFT_1024);
	_delay_ms(100);
	setreg(0x07, ATTENUATION_OFF);
	
	/* Program loop */
	for(;;) {
		_delay_ms(1000);
		setreg(0x01, ATTENUATION_2DB);
		_delay_ms(1000);
		setreg(0x01, ATTENUATION_OFF);
		_delay_ms(1000);
		setreg(0x03, ATTENUATION_2DB);
		_delay_ms(1000);
		setreg(0x03, ATTENUATION_OFF);
		_delay_ms(1000);
		setreg(0x05, ATTENUATION_2DB);
		_delay_ms(1000);
		setreg(0x05, ATTENUATION_OFF);
		_delay_ms(1000);
		setreg(0x07, ATTENUATION_2DB);
		_delay_ms(1000);
		setreg(0x07, ATTENUATION_OFF);
	}
	
	/* Compiler fix */
	return 0;
}
