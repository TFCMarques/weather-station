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

int windAlert = 12557; // 66% of max value
int humidityAlert = 675; // 66% of max value
int temperatureAlert = 102; // 66% of max value

int altWindAlert = 9514; // 50% of max value
int altHumidityAlert = 514; // 50% of max value
int altTemperatureAlert = 78; // 50% of max value

int main() {
    char message[64];
    int passwordOK = FALSE;
    
    initUART();
    initADC();
    initLCD();
//    initI2C();
    initPWM();
    startPWM();

    do {
        clearLCD();
        setCursorLCD(0, 0);
        writeStringLCD("Password: ");
        passwordOK = checkPassword();
        sleep(500);
    } while(!passwordOK);
    
    clearLCD();
    setCursorLCD(0, 0);
    writeStringLCD("> SAD 2019/2020");
    setCursorLCD(1, 0);
    writeStringLCD("> Status: Okay");
    
//    writeByteEEPROM(0x0000, 'K');
//    if(readByteEEPROM(0x0000) != 'K') return 1;
    
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
            // Wind Speeds Range: 0 to 19027
            // Humidity Range: 0 to 1023
            // Temperature Range: 0 to 157
            int newW = windMeasured;
            int newH = measureHumidity();
            int newT = measureTemperature();
            
            // Warning situation 1: Wind Gusts
            if(lastW != -1 && newW >= windAlert) {
                warningFlag = 1;
                warningAlert();
                setCursorLCD(1, 0);
                writeStringLCD("> Status: Warn");
                sprintf(message,
                        "{ \"Warning\" : 1, \"W\" : %d, \"H\" : %d, \"T\": %d }",
                        newW, newH, newT);
                sendStringUART(message);
                sleep(100);
            // Warning situation 2: Heavy Rainfall
            } else if(newH > humidityAlert) {
                warningFlag = 1;
                warningAlert();
                setCursorLCD(1, 0);
                writeStringLCD("> Status: Warn");
                sprintf(message,
                        "{ \"Warning\" : 2, \"W\" : %d, \"H\" : %d, \"T\": %d }",
                        newW, newH, newT);
                sendStringUART(message);
                sleep(100);
                // Warning situation 3: Wildfire Hazard
            } else if(newW >= windAlert && newH <= humidityAlert && newT >= temperatureAlert) {
                warningFlag = 1;
                warningAlert();
                setCursorLCD(1, 0);
                writeStringLCD("> Status: Warn");
                sprintf(message,
                        "{ \"Warning\" : 3, \"W\" : %d, \"H\" : %d, \"T\": %d }",
                        newW, newH, newT);
                sendStringUART(message);
                sleep(100);
            }

            if (warningFlag == 0) {
                setCursorLCD(1, 0);
                writeStringLCD("> Status: Okay");
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
        
        char option = getCharUART();

        if(option == 'X' && lastW != -1) {
            int newH = measureHumidity();
            int newT = measureTemperature();

            sprintf(message,
                    "{ \"W\" : %d, \"H\" : %d, \"T\": %d }",
                    lastW, newH, newT);
            sendStringUART(message);
            sleep(100);

            lastH = newH;
            lastT = newT;
        } else if(option == 'Y') {
            int aux0 = windAlert;
            int aux1 = humidityAlert;
            int aux2 = temperatureAlert;

            windAlert = altWindAlert;
            humidityAlert = altHumidityAlert;
            temperatureAlert = altTemperatureAlert;

            altWindAlert = aux0;
            altHumidityAlert = aux1;
            altTemperatureAlert = aux2;
        }
        
        // Resets message memory
        memset(message, 0, sizeof(message));
    }
    
    return 0;
}

void __interrupt() isr() {
    if(TMR0IF == 1) {
        TMR0IF = 0;
        counterTimer0++;
        
        // Using aprox. 30 seconds
        // 60 seconds overflows fan speed counter
        if (counterTimer0 == 125 * 30) {
            counterTimer0 = 0;
            sendingMsg = 1;
            windMeasured = measureWindSpeed();
            
            TMR1 = 0;
            TMR0 = 0;
        }
    }
}
