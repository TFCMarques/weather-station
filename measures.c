#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commons.h"
#include "uart.h"
#include "adc.h"
#include "pwm.h"

void setWindSpeed() {
    char dutyCycle[30];
    int windPot = readADC(AN0_WIND);
    int dcRate = setDutyCyclePWM(windPot);
    sprintf(dutyCycle, "Duty Cycle: %d", dcRate);
    sendStringUART(dutyCycle);
}

void measureWindSpeed() {
    char speed[30];
    int rpm = ((TMR1H<<8) + TMR1L) / 7;
    sprintf(speed, "Wind (RPM): %d", rpm);
    sendStringUART(speed);
}

void measureHumidity() {
    char humidity[30];
    int humidityLevel = readADC(AN1_HUMIDITY) / (1023 * 0.01);
    sprintf(humidity, "Humidity (percentage): %d", humidityLevel);
    sendStringUART(humidity);
}

void measureTemperature() {
    char temperature[30];
    int tempValue = 5 * readADC(AN2_TEMPERATURE) * 100 / 1023;
    sprintf(temperature, "Temperature (Celcius): %d", tempValue);
    sendStringUART(temperature);
}

void changeTemperature() {
    //TRISCbits.TRISC5 = 0;
    
    if(PORTCbits.RC5 == 0) {
        PORTCbits.RC5 = 1;
    } else {
        PORTCbits.RC5 = 0;
    }
}
