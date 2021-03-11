/*
 * main.c
 *
 * Created: 1/16/2021 6:40:05 PM
 *  Author: Darren Lee
 */ 

#include <xc.h>
#include "avr.h"

#define LED 0
#define BUTTON 0 

void instWait()
{
	int i;
	for(i = 0; i < 32000; i++)
	{
		//wait
	}
}

int main(void)
{
	
	//DDRB = 0x00;//input
	//PORTB = 0xFF;//portd internal pullup
	//DDRA = 0x01;//portA as output
	//PORTA = 0x00;
	
	SET_BIT(DDRA,LED); //set pin A0 to output
	PORTA = 0x00;
	CLR_BIT(DDRB,BUTTON); // set pin B0 for b to input
	PORTB = 0xFF;
    while(1)
    {
		if(!(PINB & (1<<PD0)))
		{
			PORTA |= 0x01;
			//instWait();
			avr_wait(500);
			PORTA &= 0xFE;
			//instWait();
			avr_wait(500);
		}else
			PORTA = 0x00;
    }
}
