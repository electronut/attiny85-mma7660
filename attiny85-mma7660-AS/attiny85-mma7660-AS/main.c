/*
 * attiny85-mma7660-AS.c
 *
 * Created: 21-11-2015 10:06:02
 * Author : mahesh
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "i2cmaster.h"

// 6-bit value to g value lookup table
// From APPENDIX C - MMA7660FC ACQUISITION CODE TABLE
float gLUT[] = {
  0.000,0.047,0.094,0.141,0.188,0.234,0.281,0.328,0.375,0.422,0.469,0.516,0.563,0.609,0.656,0.703,0.750,0.797,0.844,0.891,0.938,0.984,1.031,1.078,1.125,1.172,1.219,1.266,1.313,1.359,1.406,1.453,-1.500,-1.453,-1.406,-1.359,-1.313,-1.266,-1.219,-1.172,-1.125,-1.078,-1.031,-0.984,-0.938,-0.891,-0.844,-0.797,-0.750,-0.703,-0.656,-0.609,-0.563,-0.516,-0.469,-0.422,-0.375,-0.328,-0.281,-0.234,-0.188,-0.141,-0.094,-0.047};

// MMA7660
// set data to given register
// See Figure 12. Single Byte Write - in MMA7660 datasheet
void mma7660_set_data(uint8_t reg, uint8_t data)
{
    // issue START
    i2c_start((0x4C << 1)|0x0);
    // write register 
    i2c_write(reg);
    // write data 
    i2c_write(data);
    // issue STOP
    i2c_stop();
}


// MMA7660
// get data from given register
// See Figure 14. Single Byte Read - in MMA7660 datasheet
void mma7660_get_data(uint8_t reg, uint8_t* data)
{
    // issuse START
    i2c_start((0x4C << 1)|0x0);
    // write register
    i2c_write(reg);
    // issue Repeated START
    i2c_rep_start((0x4C << 1)|0x1);
    // read data and issue STOP
    *data = i2c_readNak();
}

unsigned char ret;
uint8_t gdata;
float ax, ay, az;

int main()
{
	
  // initialize I2C
  i2c_init();
	
  // set up MMA7660:

  // set MODE to stand by
  mma7660_set_data(0x07,0x00);

  // set up SR register
  mma7660_set_data(0x08,0x00);

  // set up interrupt register
  mma7660_set_data(0x06,0b11100100);

  // tap detection reg
  mma7660_set_data(0x09,11);
	
  // tap debounce reg
  mma7660_set_data(0x0a,11);

  // count
  mma7660_set_data(0x05, 0xff);
	
  // set MODE to active
  mma7660_set_data(0x07,0b00011001);

  DDRB = (0x1 << PB2);
    
  // main loop 
  while (1) {	
    
    uint8_t x, y, z;
    mma7660_get_data(0x00, &x);
    mma7660_get_data(0x01, &y);
    mma7660_get_data(0x02, &z);
    
    ax = gLUT[x];
    ay = gLUT[y];
    az = gLUT[z];
    
    // for debugging - breakpt
    ret = 5 + ax + ay + az;

    float aSq = ax*ax + ay*ay + az*az;
	
	// MMA7660 limit is +-1.5g
    if (aSq > 2.0 && aSq < 6.75) {
      // flash# 1:
      // set high
      PORTB |= (0x1 << PB2);
      _delay_ms(20);// set up MMA7660:
      // set low
      PORTB &= ~(0x1 << PB2);
    }
		
    //_delay_ms(250);
		
  }
}

