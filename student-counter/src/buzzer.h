#ifndef BUZZER_H
#define BUZZER_H

#include <avr/io.h>
#include <util/delay.h>

#define BUZZER_PIN PB0

void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void Buzzer_Beep(void);
void Buzzer_CriticalWarning(void);
void Buzzer_Success(void);

#endif // BUZZER_H
