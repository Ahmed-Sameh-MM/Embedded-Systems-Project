#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"

#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"

void LCD4bits_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x02;   //enable clock for PORTB
	delayMs(10);                 //delay 10 ms for enable the clock of PORTB
        LCD_DIR = 0xFF;              //let PORTB as output pins
	LCD_DEN = 0xFF;              //enable PORTB digital IO pins
	LCD4bits_Cmd(0x28);          //2 lines and 5x7 character (4-bit data, D4 to D7)
	LCD4bits_Cmd(0x06);          //Automatic Increment cursor (shift cursor to right)
	LCD4bits_Cmd(0x01);	     //Clear display screen
	LCD4bits_Cmd(0x0F);          //Display on, cursor blinking
}


void LCD_Write4bits(unsigned char data, unsigned char control)
{
	data &= 0xF0;                       //clear lower nibble for control
	control &= 0x0F;                    //clear upper nibble for data
	LCD_DATA = data | control;          //Include RS value (command or data ) with data
	LCD_DATA = data | control | EN;     //pulse EN
	delayUs(0);			    //delay for pulsing EN
	LCD_DATA = data | control;	    //Turn off the pulse EN
	LCD_DATA = 0;                       //Clear the Data
}

void LCD4bits_Cmd(unsigned char command)
{
	LCD_Write4bits(command & 0xF0 , 0);    //upper nibble first
	LCD_Write4bits(command << 4 , 0);      //then lower nibble

	if(command < 4)
		delayMs(2);                        //commands 1 and 2 need up to 1.64ms
	else
		delayUs(40);                       //all others 40 us
}


void delayMs(int n)
{
	volatile int i,j;               //volatile is important for variables incremented in code
	for(i=0;i<n;i++)
		for(j=0;j<3180;j++)     //delay for 1 msec
		{}
}

void delayUs(int n)
{
	volatile int i,j;		    //volatile is important for variables incremented in code
	for(i=0;i<n;i++)
		for(j=0;j<3;j++)            //delay for 1 micro second
		{}
}


void LCD_Command(unsigned char c) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(1000);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(1000);
        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(1000);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(1000);

}

void LCD_Show(unsigned char d) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(1000);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(1000);
        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(1000);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(1000);

}

void LCD_Cursor(char x, char y){

    if (x==0) {
        LCD_Command(0x80 + (y % 16));
        return;
    }
    LCD_Command(0xC0 + (y % 16));

}

void LCD_Clear(void){

        LCD_Command(0x01);
        SysCtlDelay(1000);

}

void LCD_Print(char *s, char *d) {
  
    LCD_Clear();
    delayUs(400);
    
    int j;
    for (j=0; j<16; j++) {
        if (j<strlen(s)) {
            LCD_Cursor(0,j);
            LCD_Show(s[j]);
        }
        if (j<strlen(d)) {
            LCD_Cursor(1,j);
            LCD_Show(d[j]);
        }
    }
    LCD_Command(0xC0 + 16); //Hide cursor
    
    delayMs(275);
}
