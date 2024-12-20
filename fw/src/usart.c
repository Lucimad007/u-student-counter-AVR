#include <avr/io.h>
#include "usart.h"

void USART_Init(unsigned long ubrr) {
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}

void USART_Transmit(char data) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

unsigned char USART_Receive(void) {
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}