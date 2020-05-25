#ifndef COMMONS_H
#define	COMMONS_H

// Auxiliary Definitions
#define TRUE 1
#define FALSE 0

// Clock frequency
#define CLK_FREQ 4000000

// Buzzer
#define BUZZER PORTCbits.RC1

// LEDs
#define LED_RB7 PORTBbits.RB7

// Buttons
#define RB3_BUTTON PORTBbits.RB3
#define RB4_BUTTON PORTBbits.RB4
#define RB5_BUTTON PORTBbits.RB5
#define RA5_BUTTON PORTAbits.RA5

// Analog Channels with ADON
#define AN0_WIND 0x01
#define AN1_HUMIDITY 0x09
#define AN2_TEMPERATURE 0x11

void sleep(int miliseconds);
void warningAlert();

#endif	/* COMMONS_H */

