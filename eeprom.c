#include <xc.h>
#include "i2c.h"
#include "eeprom.h"

#include "uart.h"

void writeByteEEPROM(unsigned int address, unsigned char byte) {
    startI2C();
    
    writeByteI2C(WRITE_ADDR);
    writeByteI2C(address);
    writeByteI2C(byte);
    
    stopI2C();
}

unsigned char readByteEEPROM(unsigned int address) {
    unsigned char byte = 0;
    
    startI2C();

    writeByteI2C(WRITE_ADDR);
    writeByteI2C(address);
    
    restartI2C();
    
    writeByteI2C(READ_ADDR);
    writeByteI2C(address);
    byte = readByteI2C();
    sendNackI2C();
    stopI2C();
    
    return byte;
}