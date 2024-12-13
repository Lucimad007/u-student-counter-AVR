#include <avr/io.h>
#include <util/delay.h>

#include "sensors.h"

int Read_Sonar(void) {
	PORTD |= (1 << TRIG);
	_delay_us(10);
	PORTD &= ~(1 << TRIG);

	while (!(PIND & (1 << ECHO)));
	TCNT1 = 0;
	TCCR1B |= (1 << CS11);

	while (PIND & (1 << ECHO));
	TCCR1B = 0;

	return TCNT1 * 0.034 / 2;
}

int Read_Temperature(void) {
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADCW;
}