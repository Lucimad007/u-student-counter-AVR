#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void LCD_Command(unsigned char cmd) {
	PORTC = cmd;
	PORTC &= ~(1 << RS); // RS = 0 for command
	PORTC |= (1 << EN);  // Enable pulse
	_delay_ms(1);
	PORTC &= ~(1 << EN);
	_delay_ms(2);
}

void LCD_Init(void) {
	DDRC = 0xFF;
	_delay_ms(20);
	LCD_Command(0x38); // 8-bit mode
	LCD_Command(0x0C); // Display ON, cursor OFF
	LCD_Command(0x01); // Clear display
}

void LCD_Print(char *str) {
	while (*str) {
		PORTC = *str++;
		PORTC |= (1 << RS); // RS = 1 for data
		PORTC |= (1 << EN);
		_delay_ms(1);
		PORTC &= ~(1 << EN);
		_delay_ms(2);
	}
}

void LCD_Clear(void) {
	LCD_Command(0x01); // Clear display
}

void LCD_SetCursor(unsigned char row, unsigned char col) {
	unsigned char pos[] = {0x80, 0xC0};
	LCD_Command(pos[row - 1] + col);
}
