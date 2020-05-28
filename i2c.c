#include <xc.h>
#include "i2c.h"
#include "commons.h"

void initI2C(void) {
    SCLK_DIR = 1;
    SDA_DIR = 1;
    
    // I2C Master Mode --> CLK = OSC / (4 * (SSPADD + 1))
    SSPADD = (unsigned char) (CLK_FREQ / (4 * 100000)) - 1;

    // Select and enable I2C in master mode
    SSPCON  = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
}


void startI2C(void) {
    SEN = 1;
    while(SEN);
}

void restartI2C(void) {
    RSEN = 1;
    while(RSEN);
}

void stopI2C(void) {
    PEN = 1;
    while(PEN);
}

void sendAckI2C(void) {
    SSPIF = 0;
    
    // Acknowledge = 0
    ACKDT = 0;
    ACKEN = 1;
    while(!SSPIF);
}

void sendNackI2C(void) {
    SSPIF = 0;
    
    // Not Acknowledge = 1
    ACKDT = 1;
    ACKEN = 1;
    while(!SSPIF);
}

char writeByteI2C(unsigned char byte) {
    SSPBUF = byte;
    
    while(BF);
    while(R_nW);
    
    // Returns ACK/NACK from slave
    return ACKSTAT;
}

char readByteI2C(void) {
    RCEN = 1;
    while(RCEN);
    
    while(!SSPIF);
    SSPIF = 0;
    
    // Returns what is in the buffer
    return SSPBUF;
}