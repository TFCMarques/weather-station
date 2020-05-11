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
    char aux[50];
    
    initUART();
    initADC();
    
    while (1) {
        sendStringUART("Hello World");
        addNewline();
        int temp = readADC(AN2_TEMPERATURE);
        sprintf(aux, "Temperature value: %d", temp);
        sendStringUART(aux);
        addNewline();
        sleep(1000);
    }
}
