#ifndef EEPROM_H
#define	EEPROM_H

#define WRITE_ADDR 0xA0
#define READ_ADDR 0xA1

void writeByteEEPROM(unsigned int address, unsigned char byte);
unsigned char readByteEEPROM(unsigned int address);

#endif	/* EEPROM_H */

