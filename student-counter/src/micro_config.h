#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#define F_CPU 8000000UL // 8 MHz clock frequency
#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>  //just for testing

#endif 