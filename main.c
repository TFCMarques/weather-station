#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom Libraries
#include "adc.h"
#include "uart.h"
#include "commons.h"
#include "screen.h"

#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit
#pragma config PWRTE = OFF // Power-up Timer Enable bit
#pragma config BOREN = OFF // Brown-out Reset Enable bit
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit
#pragma config WRT = OFF // Flash Program Memory Write Enable bits
#pragma config CP = OFF // Flash Program Memory Code Protection bit

int main(void) {
    initUART();
    initADC();
    sendStringUART("Init UART");
    lcd_init();
    sendStringUART("Init LCD");
    lcd_cmd(L_NCR);
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("   LCD Test");
  
    for(int i=32;i>=32;i++) {
        if((i%16) == 0)lcd_cmd(L_L2); 
        lcd_dat(i);
        sleep(50);
    }
    
    sleep(100);
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("   LCD Test");
    lcd_cmd(L_L2);
    lcd_str("       Ok");
    sleep(500);
}
