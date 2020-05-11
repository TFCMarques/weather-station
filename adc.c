#include <xc.h>
#include "adc.h"
#include "commons.h"

void initADC() {
    // ADC module turned on and CLK is selected
    ADCON0 = 0x00;

    // All pins as analog input 
    ADCON1 = 0x80;

    // Set port A as input
    TRISA = 0xFF;
}

int readADC(int channel) {
    // Takes channel bits and ADCON bit
    ADCON0 = channel;
    sleep(1000);

    // Starts converting
    GO = 1;
    while(GO_DONE==1);
    return ((ADRESH<<8) + ADRESL);
}