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
#include "lcd.h"
#include "i2c.h"
#include "eeprom.h"

#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit
#pragma config PWRTE = OFF // Power-up Timer Enable bit
#pragma config BOREN = OFF // Brown-out Reset Enable bit
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit
#pragma config WRT = OFF // Flash Program Memory Write Enable bits
#pragma config CP = OFF // Flash Program Memory Code Protection bit

int counterTimer0 = 0;
int windMeasured = 0;
int warningFlag = 0;
int sendingMsg = 0;

int lastW = -1;
int lastH = -1;
int lastT = -1;

int main() {
    //int passwordOK = FALSE;
    
    initUART();
    initADC();
    //initI2C();
    initPWM();
    startPWM();
    
    //do {
    //    sendStringUART("Insert Password:");
    //    passwordOK = checkPassword();
    //    sleep(100);
    //} while(!passwordOK);
    
    //writeByteEEPROM(0x0000, 'K');

    initInterrupFlags();
    initTimer0();
    initTimer1();
    
    while(TRUE) {        
        int currentW = getWindPWM();
        setWindSpeed(currentW);
        
        if(!RB3_BUTTON) {
            while(!RB3_BUTTON);
            changeTemperature();
        }
        
        if(sendingMsg == 1) {
            char message[64];
            
            // Wind Speeds Range: 0 to 19027
            // Humidity Range: 0 to 1023
            // Temperature Range: 0 to 156
            int newW = windMeasured;
            int newH = measureHumidity();
            int newT = measureTemperature();
            
            // Warning situation 1: Wind Gusts
            if(lastW != -1 && newW >= lastW + 500) {
                warningFlag = 1;
                warningAlert();
                sprintf(message,
                        "{ \"Warning\" : 1, \"W\" : %d, \"H\" : %d, \"T\": %d }",
                        newW, newH, newT);
                sendStringUART(message);
                sleep(100);
            // Warning situation 2: Heavy Rainfall
            } else if(newH > 675) {
                warningFlag = 1;
                warningAlert();
                sprintf(message,
                        "{ \"Warning\" : 2, \"W\" : %d, \"H\" : %d, \"T\": %d }",
                        newW, newH, newT);
                sendStringUART(message);
                sleep(100);
                // Warning situation 3: Wildfire Hazard
            } else if(newW >= 12557 && newH <= 337 && newT >= 52) {
                warningFlag = 1;
                warningAlert();
                sprintf(message,
                        "{ \"Warning\" : 3, \"W\" : %d, \"H\" : %d, \"T\": %d }",
                        newW, newH, newT);
                sendStringUART(message);
                sleep(100);
            }

            if (warningFlag == 0) {
                sprintf(message,
                        "{ \"W\" : %d, \"H\" : %d, \"T\": %d }",
                        newW, newH, newT);
                sendStringUART(message);
                sleep(100);
            } else warningFlag = 0;

            lastW = newW;
            lastH = newH;
            lastT = newT;
            sendingMsg = 0;
        }
    }
}

void __interrupt() isr() {
    if(TMR0IF == 1) {
        TMR0IF = 0;
        counterTimer0++;

        if (counterTimer0 == 125 * 60) {
            counterTimer0 = 0;
            sendingMsg = 1;
            windMeasured = measureWindSpeed();
            
            TMR1 = 0;
            TMR0 = 0;
        }
    }
}