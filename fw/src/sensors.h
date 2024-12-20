#ifndef SENSORS_H
#define SENSORS_H

void ADC_Init(void);
int ADC_Read(char channel);
float toCelsius(int readADC);

#endif
