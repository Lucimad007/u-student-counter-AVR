#ifndef SENSORS_H
#define SENSORS_H

#define TRIG PD0  // Define Trigger pin as PORTD pin 0
#define ECHO PD1  // Define Echo pin as PORTD pin 1

void Sensors_Init(void);
int Sensors_Read(void);

#endif
