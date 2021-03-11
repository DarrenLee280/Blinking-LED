/*
 * main.c
 *
 * Created: 3/5/2021 1:21:21 PM
 *  Author: Darren Lee
 */ 

#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "avr.h"
#include "lcd.h"


#define TIME 500
#define LINE 16
	

typedef struct statistics{
	int current; // current v
	int min; //minimum v
	int max; // maximum v
	int num; // number of probs
	long total;	 //total
} statistics;

statistics stats;

int is_pressed(int row, int column) {
	//Set all pins of PORTC to N/C
	DDRC = 0x00;
	PORTC = 0x00;
	//Set PORTC @ location row to "0"
	SET_BIT(DDRC, row);
	CLR_BIT(PORTC, row);
	//Set PORTC @ location column to "w1"
	CLR_BIT(DDRC, column + 4);
	SET_BIT(PORTC,column + 4);
	avr_wait(1);
	//if pin c @ column is "1"
	if(GET_BIT(PINC, column + 4) == 0){
		return 1;
	}else
	return 0;
	//return 0; else return 1;
}

int get_key() {
	int r,c;
	for(r=0;r<4;++r){
		for(c=0;c<4;++c){
			if(is_pressed(r,c)){
				return 1 + ((r * 4 - r) + c);
			}
		}
	}
	return -1;
}

int get_sample(){
	//config the mux
	//enable converter
	//start conversion
	CLR_BIT(ADMUX,0);
	CLR_BIT(ADMUX,1);
	CLR_BIT(ADMUX,2);
	CLR_BIT(ADMUX,3);
	CLR_BIT(ADMUX,4);

	SET_BIT(ADCSRA,6);

	while(!GET_BIT(ADCSRA,4)){}
		
	SET_BIT(ADCSRA,4);

	return (ADC); // this returns 0 - 1023
}

void update_statistics(int s){
		if(stats.num >= ULONG_MAX){
			stats.num = 0;
		}

		if(stats.total >= ULONG_MAX){
			stats.total = 0;
		}
	 stats.current = s;
	 stats.total += stats.current;
	 stats.num++;
	 if(s < stats.min){
		 stats.min = s;
	 }
	 
	 if(s > stats.max){
		 stats.max = s;
	 }
}

void display(int s){
	lcd_clr();
	int curr, max, min, avg;
	char buffer1[17]; // first line of the LCD
	char buffer2[17]; // second line of the LCD
	
	//calculate current voltage
	curr = (((unsigned long) (stats.current)) * 5 * 100) / 1023;
	int digitCurr = curr / 100;
	int decCurr = curr % 100;
	
	//calculate avg voltage
	avg = (((unsigned long) (stats.total / stats.num)) * 5 * 100) / 1023;
	int digitAvg = avg / 100;
	int decAvg = avg % 100;
	
	// calculate max voltage
	max = (((unsigned long) (stats.max)) * 5 * 100) / 1023;
	int digitMax = max / 100;
	int decMax = max % 100;
	
	
	//calculate min voltage
	min = (((unsigned long) (stats.min)) * 5 * 100) / 1023;
	int digitMin = min / 100;
	int decMin = min % 100;
	
	//sprintf(buffer1, "C:%4.2f  A:%4.2f",curr, avg);
	sprintf(buffer1, "C:%1d.%02d Avg:%1d.%02d", digitCurr, decCurr, digitAvg, decAvg);
	lcd_pos(0,0);
	lcd_puts(buffer1);
	sprintf(buffer2, "Mx:%1d.%02d Mn:%1d.%02d", digitMax, decMax, digitMin, decMin);
	lcd_pos(1,0);
	lcd_puts(buffer2);
}

void updateReset(int s){
	stats.current = s;
}

void resetVolt(){
	stats.max = 0;
	stats.min = 1023;
	stats.num = 0;
	stats.total = 0;
}

void displayReset(){
	lcd_clr();
	int curr;
	char buff[17];
	
	//calculate current voltage
	curr = (((unsigned long) (stats.current)) * 5 * 100) / 1023;
	int digitCurr = curr / 100;
	int decCurr = curr % 100;
	
	sprintf(buff, "C:%d.%02d  A: ---", digitCurr, decCurr);
	lcd_pos(0,0);
	lcd_puts(buff);
	lcd_pos(1,0);
	lcd_puts("Mx: ---  Mn: ---");
}

int main(void)
{
	lcd_init();
	
	CLR_BIT(ADMUX,7);
	SET_BIT(ADMUX,6);
	
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
	
	stats.min = 1023;
	stats.max = 0;
	stats.current = 0;
	
	
	int s;
	int key;
	int reset = 0;
	int sample = 1;
    while(1)
    {
		key = get_key();
		if(key > 0){
			//reset
			if(key == 1){
				reset = 1;
				sample = 0;
			}
			
			if(key == 2){
				reset = 0;
				sample = 1;
			}
		}
		if(sample) {
			avr_wait(TIME);
			s = get_sample();
			update_statistics(s);
			display(s);
		}
		
		if(reset){
			avr_wait(TIME);
			s = get_sample();
			updateReset(s);
			resetVolt();
			displayReset();
		}
    }
}