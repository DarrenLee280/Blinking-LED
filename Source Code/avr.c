/*
 * CFile1.c
 *
 * Created: 1/29/2021 8:54:55 PM
 *  Author: Darren Lee
 */ 
#include "avr.h"

void
avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}