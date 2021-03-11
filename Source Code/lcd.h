/*
 * lcd.h
 *
 * Created: 2/18/2021 5:29:17 PM
 *  Author: Darren Lee
 */ 


#ifndef LCD_H_
#define LCD_H_


void lcd_init(void);

void lcd_clr(void);

void lcd_pos(unsigned char r, unsigned char c);

void lcd_put(char c);

void lcd_puts(const char *s);


#endif /* LCD_H_ */