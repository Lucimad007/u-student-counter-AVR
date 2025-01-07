#include "buzzer.h"

void buzzer_init()
{
	BUZZER_DDR |= (1<<BUZZER_POS); // Set output
	// _delay_ms(5);
}

void buzzer_start()
{
	BUZZER_PORT |= (1 << BUZZER_POS); // Put 1 on BUZZER_POS of BUZZER_PORT
}

void buzzer_stop()
{
	BUZZER_PORT &= ~(1 << BUZZER_POS); // Put 0 on BUZZER_POS of BUZZER_PORT
}

void small_beep(uint16_t t_ms)
{
	buzzer_start();
	for (uint16_t i = 0; i < t_ms; i+=10)
	{
		_delay_ms(10);
	}
	buzzer_stop();
}