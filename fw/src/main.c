#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"
#include "eeprom.h"
#include "sensors.h"

#define F_CPU 16000000UL

void Show_Menu(void);

void Show_Menu(void) {
	LCD_Clear();
	LCD_Print("1. Attendance");
	LCD_SetCursor(2, 0);
	LCD_Print("2. Sensors");
}

void main(void) {
	LCD_Init();
	
	while (1) {
		Show_Menu();
		//char key = Keypad_GetKey();
//
		//if (key == '1') {
			//LCD_Clear();
			//LCD_Print("Recording...");
			//EEPROM_Write(0x00, 'P');
			//_delay_ms(1000);
			//} else if (key == '2') {
			//LCD_Clear();
			//char buffer[16];
			//int temp = Read_Temperature();
			//snprintf(buffer, sizeof(buffer), "Temp: %d", temp);
			//LCD_Print(buffer);
			//_delay_ms(2000);
		//}
	}
}
