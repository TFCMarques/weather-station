#ifndef KEYPAD_H
#define	KEYPAD_H

#define COLUMN1 PORTBbits.RB0
#define COLUMN2 PORTBbits.RB1
#define COLUMN3 PORTBbits.RB2

#define ROW4 PORTDbits.RD0
#define ROW3 PORTDbits.RD1
#define ROW2 PORTDbits.RD2
#define ROW1 PORTDbits.RD3

void initKeypad();
void checkingRow(int row);
char getPressedKey();

#endif	/* KEYPAD_H */