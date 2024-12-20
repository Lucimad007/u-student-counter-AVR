#ifndef LCD_H
#define LCD_H

#define RS 0  // RS connected to PORTC pin 0
#define EN 1  // EN connected to PORTC pin 1

void LCD_Command(unsigned char cmd);
void LCD_Init(void);
void LCD_Print(char *str);
void LCD_Clear(void);
void LCD_SetCursor(unsigned char row, unsigned char col);

#endif
