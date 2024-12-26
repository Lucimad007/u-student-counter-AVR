#include <avr/io.h>
#include <util/delay.h>
#include "buzzer.h"

void Buzzer_Init(void) {
	DDRB |= (1 << BUZZER_PIN); // Set BUZZER_PIN as output
	PORTB &= ~(1 << BUZZER_PIN); // Ensure the buzzer is off initially
}

void Buzzer_On(void) {
	PORTB |= ~(1 << BUZZER_PIN); // Set BUZZER_PIN high
}

void Buzzer_Off(void) {
	PORTB &= (1 << BUZZER_PIN); // Set BUZZER_PIN low
}

void Buzzer_Beep(void) {
	Buzzer_On();
	_delay_ms(200); // Beep duration
	Buzzer_Off();
	_delay_ms(100); // Wait before next action
}

void Buzzer_CriticalWarning(void) {
	for (int i = 0; i < 3; i++) {
		Buzzer_Beep();
		_delay_ms(200); // Delay between beeps
	}
}

void Buzzer_Success(void) {
	Buzzer_On();
	_delay_ms(500); // Long beep for success
	Buzzer_Off();
}
