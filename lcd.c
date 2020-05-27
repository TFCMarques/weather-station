#include <xc.h>
#include "lcd.h"
#include "commons.h"

void portLCD(char port) {
    if(port & 1) {
        D4 = 1;
    } else D4 = 0;
    
    if(port & 2) {
        D5 = 1;
    } else D5 = 0;
    
    if(port & 4) {
        D6 = 1;
    } else D6 = 0;
    
    if(port & 8) {
        D7 = 1;
    } else D7 = 0;
}

void commandLCD(char command) {
    RS = 0;
    portLCD(command);
    EN = 1;
    sleep(10);
    EN = 0;
}

void clearLCD() {
    commandLCD(0x00);
    commandLCD(0x01);
}

void setCursorLCD(char line, char column) {
    char aux;
    
    if(line == 0) {
        aux = 0x80 + column;
    } else if(line == 1) {
        aux = 0xC0 + column;
    }
    
    commandLCD(aux>>4);
    commandLCD(aux & 0x0F);
}

void initLCD() {
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;
    
    portLCD(0x00);
    sleep(20);
    commandLCD(0x03);
    sleep(10);
    commandLCD(0x03);
    sleep(15);
    
    commandLCD(0x03);
    commandLCD(0x02);
    commandLCD(0x02);
    commandLCD(0x08);
    commandLCD(0x00);
    commandLCD(0x0C);
    commandLCD(0x00);
    commandLCD(0x06);
}

void writeCharLCD(char aux) {
    RS = 1;
    portLCD((aux & 0xF0)>>4);
    EN = 1;
    sleep(10);
    EN = 0;
    portLCD(aux & 0x0F);
    EN = 1;
    sleep(10);
    EN = 0;
}

void writeStringLCD(char* string) {
    while(*string) writeCharLCD(*string++);
}

void shiftRightLCD() {
    commandLCD(0x01);
    commandLCD(0x0C);
}

void shiftLeftLCD() {
    commandLCD(0x01);
    commandLCD(0x08);
}