#ifndef GLCD_H_
#define GLCD_H_


#define F_CPU 8000000UL			/* Define CPU clock Frequency 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include defined delay header file */
#include <stdio.h>
#include <avr/pgmspace.h>

#define Data_Port		PORTA	/* Define data port for GLCD */
#define Command_Port		PORTC	/* Define command port for GLCD */
#define Data_Port_Dir		DDRA	/* Define data port for GLCD */
#define Command_Port_Dir	DDRC	/* Define command port for GLCD */

#define RS			PC0	/* Define control pins */
#define RW			PC1
#define EN			PC2
#define CS1			PC3
#define CS2			PC4
#define RST			PC5

#define TotalPage		8

void GLCD_Command(char Command);
void GLCD_Data(char Data);
void GLCD_Init(void);
void GLCD_ClearAll(void);
void GLCD_String(const char* image);


#endif 