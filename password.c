#include <xc.h>
#include <string.h>
#include "keypad.h"
#include "uart.h"
#include "commons.h"

int checkPassword() {
    char* systemPassword = "1234";
    char receivedPassword[5];

    initKeypad();
    sleep(100);
    for(int i = 0; i < 4; i++) {
        receivedPassword[i] = getPressedKey();
        sendCharUART(receivedPassword[i]);
    }
    
    addNewline();
    receivedPassword[4] = '\0';
    
    if (strcmp(receivedPassword, systemPassword) == 0) {
        sendStringUART("Correct password.");
        return TRUE;
    } else {
        sendStringUART("Wrong password.");
        return FALSE;
    }
}