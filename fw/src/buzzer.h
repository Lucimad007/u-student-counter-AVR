#ifndef BUZZER_H
#define BUZZER_H

#include <avr/io.h>
#include <util/delay.h>

#define BUZZER_PIN PA1
#define BUZZER_PORT_OUT PORTA
#define BUZZER_PORT_IN  PINA
#define BUZZER_PORT_DIR DDRA


void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void Buzzer_Beep(void);
void Buzzer_CriticalWarning(void);
void Buzzer_Success(void);

#endif // BUZZER_H
