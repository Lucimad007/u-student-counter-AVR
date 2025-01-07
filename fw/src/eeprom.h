#ifndef EEPROM_H
#define EEPROM_H

#define EEPROM_SIZE 1024 // ATmega32 EEPROM

void EEPROM_Write(unsigned int address, unsigned char data);
unsigned char EEPROM_Read(unsigned int address);
void EEPROM_Clear(void) ;
void EEPROM_WriteString(unsigned int startAddress, const char* str);
void EEPROM_ReadString(unsigned int startAddress, char* buffer, unsigned int length);
unsigned int EEPROM_FindNextAddress(void);

#endif