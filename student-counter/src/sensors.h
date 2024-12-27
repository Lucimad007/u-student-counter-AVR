#ifndef SENSORS_H
#define SENSORS_H

#define degree_sysmbol 0xdf

void ADC_Init(void);
int ADC_Read(char channel);
float toCelsius(int readADC);

#endif
