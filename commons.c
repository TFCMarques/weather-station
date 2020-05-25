#include <xc.h>
#include "commons.h"

void sleep(int miliseconds) {
    for(int i = 0; i < miliseconds; i++) {
        for(int j = 0; j < 100; j++);
    }
}

void warningAlert() {
    int stateLED = LED_RB7;
    int stateTRISB7 = TRISBbits.TRISB7;
    int stateTRISC1 = TRISCbits.TRISC1;
    
    TRISBbits.TRISB7 = 0;
    TRISCbits.TRISC1 = 0;
    
    for(int i = 0; i < 3; i++) {
        LED_RB7 = 1;
        BUZZER = 1;
        sleep(100);
        LED_RB7 = 0;
        BUZZER = 0;
        sleep(100);
    }
    
    LED_RB7 = stateLED;
    TRISBbits.TRISB7 = stateTRISB7;
    TRISCbits.TRISC1 = stateTRISC1;
}
