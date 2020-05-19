#include <xc.h>
#include "uart.h"
#include "commons.h"

void initUART() {
    // Setting I/O pins for UART
    TRISC=0x80;

    // Initialize SPBRG with 9,6kHz BR with BRGH as fast BR
    BRGH = TRUE;
    SPBRG = 25;

    // Enable asynchronous serial port
    SYNC = FALSE;
    SPEN = TRUE; 

    // Enable transmission and reception in 8-bit mode
    TXEN = TRUE;
    CREN = TRUE;
    TX9 = 0;
    RX9 = 0;
}

void sendCharUART(char aux) {
    while(!TXIF);
    TXREG = aux;
}

void sendStringUART(const char* string) {
    while(*string) sendCharUART(*string++);
    addNewline();
}

char getCharUART() {
    while(!RCIF);
    return RCREG;
}

void addNewline() {
    sendCharUART('\n');
	sendCharUART('\r');
}