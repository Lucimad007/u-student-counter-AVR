#include <avr/io.h>
#include "eeprom.h"

void EEPROM_Write(unsigned int address, unsigned char data) {
	while (EECR & (1 << EEWE));
	EEAR = address;
	EEDR = data;
	EECR |= (1 << EEMWE);
	EECR |= (1 << EEWE);
}

unsigned char EEPROM_Read(unsigned int address) {
	while (EECR & (1 << EEWE));
	EEAR = address;
	EECR |= (1 << EERE);
	return EEDR;
}