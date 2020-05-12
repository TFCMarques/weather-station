#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom Libraries
#include "adc.h"
#include "uart.h"
#include "commons.h"

#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit
#pragma config PWRTE = OFF // Power-up Timer Enable bit
#pragma config BOREN = OFF // Brown-out Reset Enable bit
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit
#pragma config WRT = OFF // Flash Program Memory Write Enable bits
#pragma config CP = OFF // Flash Program Memory Code Protection bit

int main(void) {
    char t[50];
    char h[50];
    char w[50];

    initUART();
    sendStringUART("UART initialized..."); addNewline();
    initADC();
    sendStringUART("ADC initialized..."); addNewline();
    
    while (TRUE) {
        if(!RB3_BUTTON) {
            int temperature = readADC(AN2_TEMPERATURE);
            sprintf(t, "Temperature value: %d", temperature);
            sendStringUART(t); addNewline();
        }
        
        if(!RB4_BUTTON) {
            int humidity = readADC(AN1_HUMIDITY);
            sprintf(h, "Humidity value: %d", humidity);
            sendStringUART(h); addNewline();
        }
        
        if(!RB5_BUTTON) {
            int wind = 123123;
            sprintf(w, "Wind value: %d", wind);
            sendStringUART(w); addNewline();
        }
        
        sleep(1000);
    }
}
