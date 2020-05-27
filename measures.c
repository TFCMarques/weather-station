#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commons.h"
#include "uart.h"
#include "adc.h"
#include "pwm.h"

int getWindPWM(void) {
    return readADC(AN0_WIND);
}

void setWindSpeed(int windPot) {
    setDutyCyclePWM(windPot);
}

int measureWindSpeed(void) {
    return ((TMR1H<<8) + TMR1L);
}

int measureHumidity(void) {
    return readADC(AN1_HUMIDITY);
}

int measureTemperature(void) {
    return readADC(AN2_TEMPERATURE);
}

void changeTemperature(void) {
    //TRISCbits.TRISC5 = 0;
    
    if(PORTCbits.RC5 == 0) {
        PORTCbits.RC5 = 1;
    } else {
        PORTCbits.RC5 = 0;
    }
}
