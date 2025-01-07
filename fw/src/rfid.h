#ifndef RFID_H
#define RFID_H

#include <avr/io.h>
#include <string.h>
//#include "USART_RS232_H_file.h"
//#include "LCD16x2_4bit.h"
#include "lcd.h"
#include "rfid.h"
#include "usart.h"

void RFID_Init(void);
void RFID_Read(char* rfid_buffer);

#endif
