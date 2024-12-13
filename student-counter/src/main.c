// /*
// 	ATmega 16 UART echo program
// 	http://www.electronicwings.com
// */ 

// #define F_CPU 8000000UL			/* Define frequency here its 8MHz */
// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdlib.h>
// #include <stdio.h>

// //#define USART_BAUDRATE 9600
// #define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


// void UART_init(long USART_BAUDRATE)
// {
// 	UCSRB |= (1 << RXEN) | (1 << TXEN);/* Turn on transmission and reception */
// 	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);/* Use 8-bit character sizes */
// 	UBRRL = BAUD_PRESCALE;		/* Load lower 8-bits of the baud rate value */
// 	UBRRH = (BAUD_PRESCALE >> 8);	/* Load upper 8-bits*/
// }

// unsigned char UART_RxChar()
// {
// 	while ((UCSRA & (1 << RXC)) == 0);/* Wait till data is received */
// 	return(UDR);			/* Return the byte*/
// }

// void UART_TxChar(char ch)
// {
// 	while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
// 	UDR = ch ;
// }

// void UART_SendString(char *str)
// {
// 	unsigned char j=0;
	
// 	while (str[j]!=0)		/* Send string till null */
// 	{
// 		UART_TxChar(str[j]);	
// 		j++;
// 	}
// }

// int main()
// {
// 	char c;
// 	UART_init(9600);
	
// 	UART_SendString("\n\t Echo Test ");	
// 	while(1)
// 	{
// 		unsigned char x = 'a';     
//         _delay_ms(500);       
//         USART_Transmit(x); // Send character 'A' every 500 ms
// 	}	
// }


// written by TAs


#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL // 16 MHz clock frequency
#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)

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

void UART_SendString(unsigned char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		USART_Transmit(str[j]);	
		j++;
	}
}

void main(void) {

    USART_init(MYUBRR); // Initialize USART with the correct baud rate

    while (1) {       
        unsigned char str[] = "hello lucimad!\n";
        _delay_ms(500);       
        //UART_SendString(str); // Send character 'A' every 500 ms
        UART_SendString(str);
    }
}