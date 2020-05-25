#ifndef LCD_H
#define	LCD_H

// Pins for LCD
#define LCD_ENABLE PORTBbits.RB0
#define LCD_REG_SELECT PORTBbits.RB1
#define LCD_DB4 PORTBbits.RB4
#define LCD_DB5 PORTBbits.RB5
#define LCD_DB6 PORTBbits.RB6
#define LCD_DB7 PORTBbits.RB7

// Pins direction register
#define LCD_ENABLE_DIR TRISB0
#define LCD_REG_SELECT_DIR TRISB1
#define LCD_DB4_DIR TRISB4
#define LCD_DB5_DIR TRISB5
#define LCD_DB6_DIR TRISB6
#define LCD_DB7_DIR TRISB7

// Commands
#define LCD_ON 0x0F
#define LCD_OFF	0x08
#define LCD_CLR 0x01
#define LCD_L1 0x80
#define LCD_L2 0xC0
#define LCD_CR 0x0F		
#define LCD_NCR	0x0C	
#define LCD_SET 0x28
#define LCD_ENTRY 0x06

void initLCD();
void clearLCD();
void toggleEnableLCD();
void writeDataLCD(char data);
void writeStringLCD(char* string);
void writeCommandLCD(char command);

#endif	/* LCD_H */

