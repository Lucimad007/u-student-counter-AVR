#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"

unsigned char Keypad_GetKey(void) {
	DDRB = 0xF0; // Upper nibble output, lower nibble input
	PORTB = 0xFF; // Enable pull-up resistors

	while (1) {
		for (int col = 0; col < 4; col++) {
			PORTB = ~(1 << (col + 4));
			_delay_ms(1);

			for (int row = 0; row < 4; row++) {
				if (!(PINB & (1 << row))) {
					while (!(PINB & (1 << row)));     
					return (row * 4 + col + '0');
				}
			}
		}
	}
}