#include <xc.h>
#include "i2c.h"
#include "eeprom.h"

#include "uart.h"

void writeByteEEPROM(int address, char byte) {
    startI2C();
    
    writeByteI2C(address>>8);
    writeByteI2C((char) address);
    writeByteI2C(byte);
    
    stopI2C();
}

char readByteEEPROM(int address) {
    char byte = 0;
    
    startI2C();

    while(writeByteI2C(EEPROM_ADDR) == 1) restartI2C();

    writeByteI2C(address>>8);
    writeByteI2C((char) address);
    restartI2C();
    
    writeByteI2C(EEPROM_ADDR + 1);
    byte = readByteI2C();
    sendNackI2C();
    stopI2C();
    
    return byte;
}