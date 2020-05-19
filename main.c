#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom Libraries
#include "adc.h"
#include "uart.h"
#include "pwm.h"
#include "commons.h"

#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit
#pragma config PWRTE = OFF // Power-up Timer Enable bit
#pragma config BOREN = OFF // Brown-out Reset Enable bit
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit
#pragma config WRT = OFF // Flash Program Memory Write Enable bits
#pragma config CP = OFF // Flash Program Memory Code Protection bit

int main() {
    int counter = 0;
    initUART();
    initADC();
    initPWM();
    
    sendStringUART("Initializations complete.");
    
    startPWM();
    sendStringUART("Started PWM.");
    
    while(TRUE){
        if (SPEEDMETER == 1) {
            counter++;
        }
        
        if (!RB3_BUTTON) {
            char aux1[50];
            int windPot = readADC(AN0_WIND);
            sprintf(aux1, "AN0 value: %d", windPot);
            sendStringUART(aux1);
            int dutyCycle = setDutyCyclePWM(windPot);
            char aux2[50];
            sprintf(aux2, "Setting duty cycle with value: %d", dutyCycle);
            sendStringUART(aux2);
        }
        
        if (!RB4_BUTTON) {
            stopPWM();
            sendStringUART("Stopped PWM.");
            char aux3[50];
            sprintf(aux3, "Number of rotations during execution: %d", counter);
            sendStringUART(aux3);
        }
    }
}