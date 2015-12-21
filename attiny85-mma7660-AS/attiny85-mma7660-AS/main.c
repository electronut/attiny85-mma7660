/*
 * attiny85-mma7660-AS.c
 *
 * Created: 21-11-2015 10:06:02
 * Author : mahesh
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "i2cmaster.h"


#define SLAVE_ADDR  0x4C

unsigned char ret;
uint8_t data;

int main()
{
	
	
	i2c_init();

	//DDRB = 0b00001000;
    /* Replace with your application code */
    while (1) 
    {	
		
		
#if 0
		ret = i2c_start((0x4C << 1)|0x0);
		i2c_write(0x04);
		i2c_rep_start((0x4C << 1)|0x1);
		data = i2c_readNak();
#endif

		ret = i2c_start((0x4C << 1)|0x0);
		i2c_write(0x07);
		i2c_write(0b00011001);
		i2c_stop();
		
		_delay_ms(1);
		
		ret = i2c_start((0x4C << 1)|0x0);
		i2c_write(0x02);
		i2c_rep_start((0x4C << 1)|0x1);
		data = i2c_readNak();
		
		ret = 5;
		//i2c_stop();
		
		/*
		// flash# 1:
		// set PB3 high
		PORTB = 0b00001000;
		_delay_ms(20);
		// set PB3 low
		PORTB = 0b00000000;
		_delay_ms(20);
		*/
		
		_delay_ms(250);
		
    }
}

