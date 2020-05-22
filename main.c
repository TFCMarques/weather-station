#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom Libraries
#include "adc.h"
#include "uart.h"
#include "pwm.h"
#include "commons.h"
#include "timers.h"
#include "password.h"
#include "measures.h"

#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit
#pragma config PWRTE = OFF // Power-up Timer Enable bit
#pragma config BOREN = OFF // Brown-out Reset Enable bit
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit
#pragma config WRT = OFF // Flash Program Memory Write Enable bits
#pragma config CP = OFF // Flash Program Memory Code Protection bit

int counterTimer0 = 0;

int main() {
    //int passwordOK = FALSE;
    
    initUART();
    initADC();
    initPWM();
    startPWM();
    
    //do {
    //    sendStringUART("Insert Password:");
    //    passwordOK = checkPassword();
    //    sleep(100);
    //} while(!passwordOK);
    
    initInterrupFlags();
    initTimer0();
    initTimer1();
    
    while(TRUE) {
        //if(!RB3_BUTTON) {
        //    while(!RB3_BUTTON);
        //    int currentW = getWindPWM();
        //    setWindSpeed(currentW);
        //}
        
        int currentW = getWindPWM();
        setWindSpeed(currentW);
        
        if(!RB4_BUTTON) {
            while(!RB4_BUTTON);
            changeTemperature();
        }
    }
}

void __interrupt() isr() {
    while(!TMR0IF);
    TMR0IF = 0;
    counterTimer0++;

    if (counterTimer0 == 125) {
        counterTimer0 = 0;
        char json[64];
        
        int lastW = measureWindSpeed();
        int lastH = measureHumidity();
        int lastT = measureTemperature();
        
        sprintf(json,
                "{ \"W\" : %d, \"H\" : %d, \"T\": %d }",
                lastW, lastH, lastT);
        
        sendStringUART(json);
        TMR1 = 0;
        TMR0 = 0;
    }
}