#ifndef LCD_H
#define	LCD_H

// Pins for LCD
#define RS RE2
#define EN RE1
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

void portLCD(char port);
void commandLCD(char command);
void clearLCD();
void setCursorLCD(char line, char column);
void initLCD();
void writeCharLCD(char aux);
void writeStringLCD(char* string);
void shiftRightLCD();
void shiftLeftLCD();

#endif	/* LCD_H */

