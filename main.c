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

#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit
#pragma config PWRTE = OFF // Power-up Timer Enable bit
#pragma config BOREN = OFF // Brown-out Reset Enable bit
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit
#pragma config WRT = OFF // Flash Program Memory Write Enable bits
#pragma config CP = OFF // Flash Program Memory Code Protection bit

//int counterTimer0 = 0;
//long speed = 0;

int main() {
    int passwordOK = FALSE;
    
    initUART();
    
    do {
        sendStringUART("Insert Password:");
        passwordOK = checkPassword();
    } while(!passwordOK);
    
    while(TRUE) {
        sendStringUART("I MADE IT HERE!!!");
        sleep(100);
    }
    
}

//void __interrupt() isr() {
//    char aux[30];
//
//    while(!TMR0IF);
//    TMR0IF = 0;
//    counterTimer0++;
//
//    if (counterTimer0 == 125 * 60) {
//        counterTimer0 = 0;
//        
//        speed = ((TMR1H<<8) + TMR1L) / 7;
//        
//        sprintf(aux, "Fan speed (rps): %d", speed);
//        sendStringUART(aux);
//        TMR1 = 0;
//        TMR0 = 0;
//    }
//}