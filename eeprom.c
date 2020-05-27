#include <xc.h>
#include "i2c.h"
#include "eeprom.h"

#include "uart.h"

void writeByteEEPROM(unsigned int address, unsigned char byte) {
    startI2C();
    
    while(writeByteI2C(WRITE_ADDR)) restartI2C();
    
    writeByteI2C(address>>8);
    writeByteI2C((unsigned char) address);
    writeByteI2C(byte);
    
    stopI2C();
}

unsigned char readByteEEPROM(unsigned int address) {
    unsigned char byte = 0;
    
    startI2C();

    while(writeByteI2C(WRITE_ADDR)) restartI2C();

    writeByteI2C(address>>8);
    writeByteI2C((unsigned char) address);
    restartI2C();
    
    writeByteI2C(READ_ADDR);
    byte = readByteI2C();
    sendNackI2C();
    stopI2C();
    
    return byte;
}