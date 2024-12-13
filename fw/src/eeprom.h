#ifndef EEPROM_H
#define EEPROM_H

void EEPROM_Write(unsigned int address, unsigned char data);
unsigned char EEPROM_Read(unsigned int address);

#endif
