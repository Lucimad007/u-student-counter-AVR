
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "lcd.h"
#include "micro_config.h"

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
void USART_SendArray(long int arr[], int size){
	char buffer[10];
	for(int i=0;i<size;i++){
		ConvertLongToString(arr[i], buffer);
		LCD_Clear();
		LCD_String("Student Code: ");
		LCD_String_xy(1,0,NULL);
		LCD_String(buffer);
		for(int j=0;j<8;j++){
			USART_Transmit(buffer[j]);
			_delay_ms(100);
		}
		USART_Transmit('\r');
		_delay_ms(100);
	}
}
void ConvertLongToString(long int num, char *str) {
	int index = 0;
	int isNegative = 0;

	// Check for negative numbers
	if (num < 0) {
		isNegative = 1;
		num = -num; // Convert to positive
	}

	// Extract digits and store in reverse order
	do {
		str[index++] = (char)((num % 10) + '0'); // Convert digit to character
		num /= 10;
	} while (num != 0);

	// Append '-' if the number was negative
	if (isNegative) {
		str[index++] = '-';
	}

	// Null-terminate the string
	str[index] = '\0';

	// Reverse the string to get the correct order
	for (int start = 0, end = index - 1; start < end; start++, end--) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
	}
}
