#include "rfid.h"
#include <util/delay.h>

void RFID_Init(void) {
    USART_init(9600);    // Initialize USART with 9600 baud rate
    LCD_Init();          // Initialize LCD
    LCD_Clear();
    LCD_String_xy(0, 0,"RFID Ready:");
}

void RFID_Read(char* rfid_buffer) {
    memset(rfid_buffer, 0, 15); // Clear the buffer
    for (int i = 0; i < 12; i++) {
        rfid_buffer[i] = USART_RxChar(); // Read 12 characters from RFID
    }
    _delay_us(10);
    LCD_String_xy(0, 1,rfid_buffer);
}
