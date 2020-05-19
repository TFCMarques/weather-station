#include <xc.h>
#include "pwm.h"
#include "commons.h"
#include "uart.h"

void initPWM() {
    CCP1CON = 0x00;
    
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

    T2CONbits.TMR2ON = 1;

    PIR1bits.TMR2IF = 0;
    while(PIR1bits.TMR2IF == 0);
    PIR1bits.TMR2IF = 0;
    while(PIR1bits.TMR2IF == 0);
}

void stopPWM() {
    CCPR1L = 0;
}

int setDutyCyclePWM(long pot) {
    CCPR1L = pot * 100 / 1023;
    return CCPR1L;
}
