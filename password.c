#include <xc.h>
#include <string.h>
#include "keypad.h"
#include "lcd.h"
#include "commons.h"

int checkPassword() {
    char* systemPassword = "1234";
    char receivedPassword[5];

    initKeypad();
    sleep(100);
    for(int i = 0; i < 4; i++) {
        receivedPassword[i] = getPressedKey();
        writeCharLCD('*');
    }
    
    setCursorLCD(1, 0);
    receivedPassword[4] = '\0';
    
    if (strcmp(receivedPassword, systemPassword) == 0) {
        writeStringLCD("> Correct");
        return TRUE;
    } else {
        writeStringLCD("> Wrong");
        return FALSE;
    }
}