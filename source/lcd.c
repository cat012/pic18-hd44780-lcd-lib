// lcd.c
// 17-May-2020


#include "lcd.h"

extern const uint8_t custchar[8*8];


//-----------------------------------------------------------------------------
static void lcd_bus(uint8_t data)  //write four bit
    {
    (data & 0b00000001) ? LCD_D4_SET : LCD_D4_CLR;
    (data & 0b00000010) ? LCD_D5_SET : LCD_D5_CLR;
    (data & 0b00000100) ? LCD_D6_SET : LCD_D6_CLR;
    (data & 0b00001000) ? LCD_D7_SET : LCD_D7_CLR;

    LCD_EN_SET;
    __delay_us(100);
    LCD_EN_CLR;
    }


//-----------------------------------------------------------------------------
static void lcd_write(uint8_t data)  //write data
    {
    lcd_bus(data>>4);
    lcd_bus(data);
    }


//-----------------------------------------------------------------------------
void lcd_custom(const uint8_t *data)  //loading an array of custom characters
    {
    COMMAND_MODE;
    lcd_write(CGRAM_WRITE);
    DATA_MODE;
    for(uint8_t k=0; k<64; k++) lcd_write(data[k]);
    }


//-----------------------------------------------------------------------------
void lcd_init(void)
    {
    LCD_RS_CLR;
    LCD_RS_OUT;

    LCD_EN_CLR;
    LCD_EN_OUT;

    LCD_D4_CLR;
    LCD_D4_OUT;

    LCD_D5_CLR;
    LCD_D5_OUT;

    LCD_D6_CLR;
    LCD_D6_OUT;

    LCD_D7_CLR;
    LCD_D7_OUT;

    //init LCD controller
    COMMAND_MODE;
    __delay_ms(20); //delay on power up
    lcd_bus(0b0011);
    __delay_ms(5); //wait for the instruction to complete
    lcd_bus(0b0011);
    __delay_us(200); //wait for the instruction to complete
    lcd_bus(0b0011);
    __delay_us(200);
    lcd_bus(0b0010); //enable 4-bit mode
    __delay_us(50);
    lcd_bus(0b0010);
    lcd_bus(0b1000); //4-bit mode, 2-line, 5x8 font
    __delay_us(50);
    lcd_bus(0b0000);
    lcd_bus(0b1000); //display off
    __delay_us(50);
    lcd_bus(0b0000);
    lcd_bus(0b0001); //display clear
    __delay_ms(5);
    lcd_bus(0b0000);
    lcd_bus(0b0110); //entry mode set
    __delay_us(50);

    lcd_bus(0b0000);
    lcd_bus(0b1100); //display on, cursor off, blink off
    __delay_us(50);

    lcd_custom(custchar);
    }


//-----------------------------------------------------------------------------
void lcd_clear(void) //clear screen
    {
    COMMAND_MODE;
    lcd_write(DISPLAY_CLR);
    __delay_ms(5);
    }


//-----------------------------------------------------------------------------
void lcd_goto(uint8_t line, uint8_t column)  //line 0..1, column 0..39
    {
    COMMAND_MODE;
    lcd_write(DDRAM_WRITE | ((line & 0x01)<<6) + column);
    }


//-----------------------------------------------------------------------------
void lcd_char(uint8_t sign) //print a character
    {
    DATA_MODE;
    lcd_write(sign);
    }


//-----------------------------------------------------------------------------
void lcd_print(const char *str) //print a string
    {
    for(; *str; str++) lcd_char(*str);
    }


//-----------------------------------------------------------------------------
void lcd_left(void)
    {
    COMMAND_MODE;
    lcd_write(SCR_RIGHT);
    }


//-----------------------------------------------------------------------------
void lcd_right(void)
    {
    COMMAND_MODE;
    lcd_write(SCR_LEFT);
    }


