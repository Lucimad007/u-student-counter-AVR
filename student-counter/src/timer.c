#include "timer.h"

void timer1_init() {
    TCCR1B |= (1 << WGM12); 
    TCCR1B |= (1 << CS12) | (1 << CS10); 
    OCR1A = 15625 - 1; 
    TIMSK |= (1 << OCIE1A);
    sei();
    seconds = 0;
    minutes = 0;
    permision = 1;
}


ISR(TIMER1_COMPA_vect) {
    //permision = 0;	// for testing purpose, each 1s
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++; 
    }
    if (minutes >= 15) { 
        minutes = 0; 
		permision = 0;
    }
}


