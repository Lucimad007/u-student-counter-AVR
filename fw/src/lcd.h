#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#define LCD_Data_Dir DDRC		/* Define LCD data port direction */
#define LCD_Command_Dir DDRD		/* Define LCD command port direction register */
#define LCD_Data_Port PORTC		/* Define LCD data port */
#define LCD_Command_Port PORTD		/* Define LCD data port */
#define RS PD0				/* Define Register Select (data/command reg.)pin */
#define RW PD1				/* Define Read/Write signal pin */
#define EN PD2				/* Define Enable signal pin */

void LCD_Command(unsigned char cmnd);
void LCD_Char (unsigned char char_data);	/* LCD data write function */
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);/* Send string to LCD with xy position */
void LCD_Clear(void);
void LCD_Number(unsigned int num);
#endif // LCD_H