/*
 * avr.h
 *
 * Created: 1/16/2021 7:22:02 PM
 *  Author: Darren Lee
 */ 


#ifndef AVR_H_
#define AVR_H_

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#define XTAL_FRQ 8000000lu

#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))

#define NOP() asm volatile("nop"::)

void avr_wait(unsigned short msec);

#endif /* AVR_H_ */