#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#endif