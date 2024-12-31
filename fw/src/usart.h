
#ifndef USART_H
#define USART_H

//PD0 is for RX (reciver)
//PD1 is for TX (transmiter)
void USART_init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
void UART_SendString(unsigned char *str);
void ConvertLongToString(long int num, char *str);
void USART_SendArray(long int arr[], int size);
#endif
