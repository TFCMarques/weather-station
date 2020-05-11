#ifndef COMMONS_H
#define	COMMONS_H

// Auxiliary Definitions
#define TRUE 1
#define FALSE 0

// Buttons
#define RB3_BUTTON PORTBbits.RB3

// Input Control
#define HEATING_RESISTANCE PORTCbits.RC5

// Analog Channels with ADON
#define AN0_WIND 0x01
#define AN1_HUMIDITY 0x09
#define AN2_TEMPERATURE 0x11

void sleep(int miliseconds);

#endif	/* COMMONS_H */

