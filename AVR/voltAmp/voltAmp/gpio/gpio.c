#include "gpio.h"

uint8_t gpioInit()
{
//---
	DDRB = 0;
	PORTB = (1 << PB7)|
			(1 << PB6)|
			(1 << PB5)|
			(1 << PB4)|
			(1 << PB3)|
			(1 << PB2)|
			(1 << PB1)|
			(1 << PB0);
//---
	DDRC |= (1 << PC5);	
	PORTC |= (1 << PC6)|
			(1 << PC5)|
			(1 << PC4)|
			(1 << PC3)|
			(1 << PC2);
//---
	DDRD = 0;
	PORTD = (1 << PD7)|
			(1 << PD6)|
			(1 << PD5)|
			(1 << PD4)|
			(1 << PD3)|
			(1 << PD2)|
			(1 << PD1)|
			(1 << PD0);
	
	return INIT_SUCCESS;
}