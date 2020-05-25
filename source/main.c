// main.c
// 23-May-2020



#include <stdio.h>
#include <stdint.h>

#include "main.h"
#include "lcd.h"


char strbuff[64]; //string buffer


//=============================================================================
void __interrupt isr_high(void)
    {
    }


//-----------------------------------------------------------------------------
void delay_ms(volatile uint16_t val)
    {
    while(val-->0) __delay_us(1000);
    }


//-----------------------------------------------------------------------------
void main(void)
    {
    IRCF2=1; IRCF1=0; IRCF0=1; //101=2MHz

    SBOREN=1; //1=enable brown out reset
    SWDTEN=0; //0=disable watchdog timer
    RBPU=1;   //0=enable pull-up

    PEIE=0; //disable interrupts
    GIE=0;

    ADCON1 = 0b001111; //disable analog inputs

    lcd_init();

    for(;;)
        {
        lcd_goto(0,0);
        lcd_print("Hello");

        static uint8_t cnt=0;

        sprintf(strbuff, "%03u", cnt++);
        lcd_goto(1,0);
        lcd_print(strbuff);

        lcd_goto(1,4);
        lcd_char(7);
        lcd_char(0);
        lcd_char(1);
        lcd_char(3);

        __delay_ms(200);
        }
    }


