#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "keypad.h"
#include "commons.h"
#include "uart.h"

void initKeypad() {
    COLUMN1 = 0;
    COLUMN2 = 0;
    COLUMN3 = 0;
    
    ROW1 = 0;
    ROW2 = 0;
    ROW3 = 0;
    ROW4 = 0;
    
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
}

void checkingRow(int row) {
    switch(row) {
        case 1: ROW1 = 0; ROW2 = 1; ROW3 = 1; ROW4 = 1; break;
        case 2: ROW1 = 1; ROW2 = 0; ROW3 = 1; ROW4 = 1; break;
        case 3: ROW1 = 1; ROW2 = 1; ROW3 = 0; ROW4 = 1; break;
        case 4: ROW1 = 1; ROW2 = 1; ROW3 = 1; ROW4 = 0; break;
        default: ROW1 = 0; ROW2 = 0; ROW3 = 0; ROW4 = 0;
    }
}

char getPressedKey() {
    char key = 'q';
    
    while (key == 'q') {
        checkingRow(1);
        sleep(10);
        if (ROW1 == 0) {
            if (COLUMN1 == 0) {
                while(COLUMN1 == 0);
                key = '1'; break;
            } else if (COLUMN2 == 0) {
                while(COLUMN2 == 0);
                key = '2'; break;
            } else if (COLUMN3 == 0) {
                while(COLUMN3 == 0);
                key = '3'; break;
            }   
        }
        
        checkingRow(2);
        sleep(10);
        if (ROW2 == 0) {
            if (COLUMN1 == 0) {
                while(COLUMN1 == 0);
                key = '4'; break;
            } else if (COLUMN2 == 0) {
                while(COLUMN2 == 0);
                key = '5'; break;
            } else if (COLUMN3 == 0) {
                while(COLUMN3 == 0);
                key = '6'; break;
            }   
        }
        
        checkingRow(3);
        sleep(10);
        if (ROW3 == 0) {
            if (COLUMN1 == 0) {
                while(COLUMN1 == 0);
                key = '7'; break;
            } else if (COLUMN2 == 0) {
                while(COLUMN2 == 0);
                key = '8'; break;
            } else if (COLUMN3 == 0) {
                while(COLUMN3 == 0);
                key = '9'; break;
            }
        }
        
        checkingRow(4);
        sleep(10);
        if (ROW4 == 0) {
            if (COLUMN1 == 0) {
                while(COLUMN1 == 0);
                key = '*'; break;
            } else if (COLUMN2 == 0) {
                while(COLUMN2 == 0);
                key = '0'; break;
            } else if (COLUMN3 == 0) {
                while(COLUMN3 == 0);
                key = '#'; break;
            }
        }
    }
    
    return key;
}