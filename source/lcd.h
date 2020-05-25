// lcd.h
// HD44780 LCD
// Compiler: XC8 V1.33
// 17-May-2020


#ifndef LCD_H
#define	LCD_H


#define _XTAL_FREQ 2000000

#include <xc.h>
#include <stdint.h>


#define LCD_RS_LAT   LATEbits.LATE0
#define LCD_RS_TRIS  TRISEbits.RE0

#define LCD_EN_LAT   LATEbits.LATE1
#define LCD_EN_TRIS  TRISEbits.RE1


#define LCD_D4_LAT   LATDbits.LATD0
#define LCD_D4_TRIS  TRISDbits.RD0

#define LCD_D5_LAT   LATDbits.LATD1
#define LCD_D5_TRIS  TRISDbits.RD1

#define LCD_D6_LAT   LATDbits.LATD2
#define LCD_D6_TRIS  TRISDbits.RD2

#define LCD_D7_LAT   LATDbits.LATD3
#define LCD_D7_TRIS  TRISDbits.RD3


#define LCD_RS_CLR  LCD_RS_LAT=0
#define LCD_RS_SET  LCD_RS_LAT=1
#define LCD_RS_OUT  LCD_RS_TRIS=0

#define LCD_EN_CLR  LCD_EN_LAT=0
#define LCD_EN_SET  LCD_EN_LAT=1
#define LCD_EN_OUT  LCD_EN_TRIS=0


#define LCD_D4_CLR  LCD_D4_LAT=0
#define LCD_D4_SET  LCD_D4_LAT=1
#define LCD_D4_OUT  LCD_D4_TRIS=0

#define LCD_D5_CLR  LCD_D5_LAT=0
#define LCD_D5_SET  LCD_D5_LAT=1
#define LCD_D5_OUT  LCD_D5_TRIS=0

#define LCD_D6_CLR  LCD_D6_LAT=0
#define LCD_D6_SET  LCD_D6_LAT=1
#define LCD_D6_OUT  LCD_D6_TRIS=0

#define LCD_D7_CLR  LCD_D7_LAT=0
#define LCD_D7_SET  LCD_D7_LAT=1
#define LCD_D7_OUT  LCD_D7_TRIS=0


#define COMMAND_MODE  LCD_RS_CLR
#define DATA_MODE     LCD_RS_SET


#define DDRAM_WRITE  0b10000000
#define CGRAM_WRITE  0b01000000

#define DISPLAY_CLR  0b00000001

#define SCR_LEFT     0b00011000
#define SCR_RIGHT    0b00011100

/*
#define CURSOR_ON    0b00000010
#define CURSOR_OFF   0b00000000

#define BLINK_ON     0b00000001
#define BLINK_OFF    0b00000000
*/


const uint8_t custchar[8*8] =  //64-byte array for 8 custom characters
 {
  0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00, //0
  0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00, //1
  0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00, //2
  0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00, //3
  0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00, //4
  0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00, //5
  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00, //6

  0b00000011,  //7
  0b00000110,
  0b00001100,
  0b00011111,
  0b00000110,
  0b00001100,
  0b00011000,
  0b00000000
 };


void lcd_custom(const uint8_t *arr);
void lcd_init(void);
void lcd_clear(void);
void lcd_goto(uint8_t line, uint8_t column);
void lcd_char(uint8_t sign);
void lcd_print(const char *str);
void lcd_right(void);
void lcd_left(void);


#endif	/* LCD_H */


