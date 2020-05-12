#ifndef COMMONS_H
#define	COMMONS_H

// Auxiliary Definitions
#define TRUE 1
#define FALSE 0

// LEDs
#define RD0_LED PORTDbits.RD0
#define RD1_LED PORTDbits.RD1
#define RD2_LED PORTDbits.RD2
#define RD3_LED PORTDbits.RD3
#define RD4_LED PORTDbits.RD4
#define RD5_LED PORTDbits.RD5
#define RD6_LED PORTDbits.RD6
#define RD7_LED PORTDbits.RD7

// Buttons
#define RB3_BUTTON PORTBbits.RB3
#define RB4_BUTTON PORTBbits.RB4
#define RB5_BUTTON PORTBbits.RB5
#define RA5_BUTTON PORTAbits.RA5

// Input Control
#define HEATING_RESISTANCE PORTCbits.RC5

// Analog Channels with ADON
#define AN1_HUMIDITY 0x09
#define AN2_TEMPERATURE 0x11

void sleep(int miliseconds);

#endif	/* COMMONS_H */

