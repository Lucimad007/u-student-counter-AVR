
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

void USART_init(unsigned int ubrr) {
	UBRRL = (unsigned char)ubrr;
	UBRRH = (unsigned char)(ubrr >> 8);
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0); // Set UCSZ1 and UCSZ0 for 8-bit data
}

void USART_Transmit(unsigned char data)
{
	while(!(UCSRA &(1<<UDRE)));
	UDR = data;
}

// ---- maybe adding SIZE parameter ---- //
void UART_SendString(unsigned char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		USART_Transmit(str[j]);
		j++;
	}
}
