#ifndef BUZZER_H
#define BUZZER_H

#define F_CPU 16000000UL
#define CPU_CLOCK 16000000
// #define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <avr/iom32.h> // Include the header file for ATmega32
#include <util/delay.h>
#include <avr/interrupt.h>

#define BUZZER_PORT PORTA
#define BUZZER_DDR DDRA
#define BUZZER_POS PA1

void buzzer_init();
void buzzer_start();
void buzzer_stop();
void small_beep(uint16_t t_ms );
#endif