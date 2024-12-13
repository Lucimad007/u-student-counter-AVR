#ifndef USART_H
#define USART_H

void USART_Init(unsigned long baud_rate);
void USART_Transmit(char data);
char USART_Receive(void);
void USART_Print(char *str);

#endif
