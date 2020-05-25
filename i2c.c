#include <xc.h>
#include "i2c.h"
#include "commons.h"

#include "uart.h"

void initI2C() {
    SCLK_DIR = 1;
    SDA_DIR = 1;
    
    // I2C Master Mode --> CLK = OSC / (4 * (SSPADD + 1))
    SSPADD = ((CLK_FREQ / 4000) / 100) - 1;

    // Select and enable I2C in master mode
    SSPCON  = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
}

void startI2C() {
    SEN = 1;
    while(!SEN);
}

void restartI2C() {
    RSEN = 1;
    while(!RSEN);
}

void stopI2C() {
    PEN = 1;
    while(!PEN);
}

void sendAckI2C() {
    SSPIF = 0;
    
    // Acknowledge = 0
    ACKDT = 0;
    ACKEN = 1;
    while(!SSPIF);
    SSPIF = 0;
}

void sendNackI2C() {
    SSPIF = 0;
    
    // Not Acknowledge = 1
    ACKDT = 1;
    ACKEN = 1;
    while(!SSPIF);
    SSPIF = 0;
}

int writeByteI2C(char byte) {
    SSPBUF = byte;
    while(BF);
    while(R_nW);
    
    // Returns ACK/NACK from slave
    return ACKSTAT;
}

char readByteI2C() {
    RCEN = 1;
    while(!SSPIF);
    SSPIF = 0;
    
    // Returns what is in the buffer
    return SSPBUF;
}