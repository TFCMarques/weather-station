#ifndef EEPROM_H
#define	EEPROM_H

#define EEPROM_ADDR 0xA0

void writeByteEEPROM(int address, char byte);
char readByteEEPROM(int address);

#endif	/* EEPROM_H */

