#include <xc.h>
#include "timers.h"
#include "commons.h"

// Timer0 works as timer
void initTimer0() {
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS0 = 0;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS2 = 1;
    
    TMR0 = 6; // counts (256 - 6) times
    
    // T = 1s = 1000000us = 32 (Prescaler) * 250 (256 - TMR0) * 125 (counter)
    // To get T = 60s ----> counter * 60
}

//Timer1 works as counter
void initTimer1() {
    T1CONbits.TMR1CS = 1;
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1CKPS1 = 0;
    
    TMR1 = 0;
    
    T1CONbits.TMR1ON = 1;
}