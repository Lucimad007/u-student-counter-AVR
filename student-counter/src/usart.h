
#ifndef USART_H
#define USART_H


void USART_init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
void UART_SendString(unsigned char *str);

#endif
