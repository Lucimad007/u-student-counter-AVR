#include "micro_config.h"
#include "std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef TIMER_H
#define TIMER_H

uint16_t seconds;
uint16_t minutes; 
unsigned char permision;

void timer1_init();

#endif