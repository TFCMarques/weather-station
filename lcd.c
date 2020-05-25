#include <xc.h>
#include "lcd.h"
#include "commons.h"


void toggleEnableLCD() {
    LCD_ENABLE = 1;
    sleep(200);
    LCD_ENABLE = 0;
    sleep(200);
}

void writeCommandLCD(char command) {
    LCD_REG_SELECT = 0;
    
    PORTB &= 0x0F;
    PORTB |= (command & 0xF0);
    toggleEnableLCD();
    
    PORTB &= 0x0F;
    PORTB |= ((command<<4) & 0xF0);
    toggleEnableLCD();
}

void writeDataLCD(char data) {
    LCD_REG_SELECT = 1;
    
    PORTB &= 0x0F;
    PORTB |= (data & 0xF0);
    toggleEnableLCD();
    
    PORTB &= 0x0F;
    PORTB |= ((data<<4) & 0xF0);
    toggleEnableLCD();
}

void initLCD() {
    // All pins output
    LCD_ENABLE = 0;
    LCD_REG_SELECT = 0;
    LCD_DB4 = 0;
    LCD_DB5 = 0;
    LCD_DB6 = 0;
    LCD_DB7 = 0;
    
    LCD_ENABLE_DIR = 0;
    LCD_REG_SELECT_DIR = 0;
    LCD_DB4_DIR = 0;
    LCD_DB5_DIR = 0;
    LCD_DB6_DIR = 0;
    LCD_DB7_DIR = 0;
    
    sleep(50);
    PORTB &= LCD_ON;        // Make Data pins zero
    PORTB |= 0x30;        // Write 0x30 value on data bus
    toggleEnableLCD();
    
    sleep(10);
    PORTB &= LCD_ON;        // Make Data pins zero
    PORTB |= 0x30;        // Write 0x30 value on data bus
    toggleEnableLCD();
    
    sleep(200);
    PORTB &= LCD_ON;        // Make Data pins zero
    PORTB |= 0x30;        // Write 0x30 value on data bus
    toggleEnableLCD();
    
    sleep(10);
    PORTB &= LCD_ON;        // Make Data pins zero
    PORTB |= 0x20;        // Write 0x20 value on data bus
    toggleEnableLCD();
    
    sleep(10);
    writeCommandLCD(LCD_SET);
    writeCommandLCD(LCD_NCR);
    writeCommandLCD(LCD_CLR);
    writeCommandLCD(LCD_ENTRY);
}
void writeStringLCD(char *string) {
    while(*string) writeDataLCD(*string++);
}
void clearLCD(void) {
    writeCommandLCD(LCD_CLR);
    sleep(50);
}