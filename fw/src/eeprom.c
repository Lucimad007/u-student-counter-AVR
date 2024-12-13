#include <avr/io.h>
#include "eeprom.h"


void EEPROM_Write(unsigned int address, unsigned char data) {
	while (EECR & (1 << EEWE)); // Wait for completion of previous write
	EEAR = address;            // Set address
	EEDR = data;               // Set data
	EECR |= (1 << EEMWE);      // Master Write Enable
	EECR |= (1 << EEWE);       // Start EEPROM write
}

unsigned char EEPROM_Read(unsigned int address) {
	while (EECR & (1 << EEWE)); // Wait for completion of previous write
	EEAR = address;            // Set address
	EECR |= (1 << EERE);       // Start EEPROM read
	return EEDR;               // Return data
}

void EEPROM_Clear(void) {
	for (unsigned int i = 0; i < EEPROM_SIZE; i++) {
		EEPROM_Write(i, 0xFF); // 0xFF is the default erased value
	}
}

void EEPROM_WriteString(unsigned int startAddress, const char* str) {
	unsigned int i = 0;
	while (str[i] != '\0' && startAddress + i < EEPROM_SIZE) {
		EEPROM_Write(startAddress + i, str[i]);
		i++;
	}
}

void EEPROM_ReadString(unsigned int startAddress, char* buffer, unsigned int length) {
	for (unsigned int i = 0; i < length && (startAddress + i) < EEPROM_SIZE; i++) {
		buffer[i] = EEPROM_Read(startAddress + i);
	}
	buffer[length] = '\0'; 
}

unsigned int EEPROM_FindNextAddress(void) {
	for (unsigned int i = 0; i < EEPROM_SIZE; i++) {
		if (EEPROM_Read(i) == 0xFF) { // 0xFF indicates an empty cell
			return i;
		}
	}
	return EEPROM_SIZE; // EEPROM is full
}
