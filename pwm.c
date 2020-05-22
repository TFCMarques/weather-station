#include <xc.h>
#include "pwm.h"
#include "commons.h"
#include "uart.h"

void initPWM() {
    CCP1CON = 0x0C;
    
    TRISCbits.TRISC0 = 1;
    TRISCbits.TRISC2 = 1;
    TRISDbits.TRISD5 = 1;
    
    PORTCbits.RC2 = 0;
    PORTDbits.RD5 = 0;
    
    PR2 = 100;
    CCPR1L = 0;
    
    T2CONbits.TMR2ON = 0;
}

void startPWM() {
    TRISCbits.TRISC2 = 0;
    TRISDbits.TRISD5 = 0;

    CCP1CON=0x0F;
    
    CCPR1L = 50;

    T2CONbits.TMR2ON = 1;
}

void stopPWM() {
    CCPR1L = 0;
}

void setDutyCyclePWM(long pot) {
    CCPR1L = pot * 100 / 1023;
}
