/*
 * attiny85-mma7660-AS.c
 *
 * Created: 21-11-2015 10:06:02
 * Author : mahesh
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "i2cmaster.h"


int main()
{
	DDRB = 0b00001000;
    /* Replace with your application code */
    while (1) 
    {
		// flash# 1:
		// set PB3 high
		PORTB = 0b00001000;
		_delay_ms(20);
		// set PB3 low
		PORTB = 0b00000000;
		_delay_ms(20);

		// flash# 2:
		// set PB3 high
		PORTB = 0b00001000;
		_delay_ms(200);
		// set PB3 low
		PORTB = 0b00000000;
		_delay_ms(200);
		
    }
}

