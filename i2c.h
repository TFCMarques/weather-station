#ifndef I2C_H
#define	I2C_H

#define SCLK PORTCbits.RC3
#define SDA PORTCbits.RC4

#define SCLK_DIR TRISC3
#define SDA_DIR TRISC4

void initI2C(void);
void waitMasterI2C(void);
void startI2C(void);
void restartI2C(void);
void stopI2C(void);
void sendAckI2C(void);
void sendNackI2C(void);
char writeByteI2C(unsigned char byte);
char readByteI2C(void);

#endif	/* I2C_H */