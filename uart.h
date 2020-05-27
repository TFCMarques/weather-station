#ifndef UART_H
#define	UART_H

// Functions Declaration
void initUART(void);
void sendCharUART(char aux);
void sendStringUART(const char* string);
char getCharUART(void);
void addNewline(void);

#endif

