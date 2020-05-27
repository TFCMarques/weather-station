#ifndef I2C_H
#define	I2C_H

#define SCLK PORTCbits.RC3
#define SDA PORTCbits.RC4

#define SCLK_DIR TRISC3
#define SDA_DIR TRISC4

void initI2C();
void waitMasterI2C();
void startI2C();
void restartI2C();
void stopI2C();
void sendAckI2C();
void sendNackI2C();
char writeByteI2C(unsigned char byte);
char readByteI2C();

#endif	/* I2C_H */