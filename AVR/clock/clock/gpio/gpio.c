#include "gpio.h"

T_INIT gpioInit(void)
{
//set all pins as INPUT PULL-UP
//PORT A
	DDRA &=	~(1 << DDA7) & ~(1 << DDA6) & ~(1 << DDA5) & ~(1 << DDA4) & ~(1 << DDA3) & ~(1 << DDA2) & ~(1 << DDA1) & ~(1 << DDA0);
	PORTA |= (1 << PA7) | (1 << PA6) | (1 << PA5) | (1 << PA4) | (1 << PA3) | (1 << PA2) | (1 << PA1) | (1 << PA0);		
//PORT B
	DDRB &= ~(1 << DDB7) & ~(1 << DDB6) & ~(1 << DDB5) & ~(1 << DDB4) & ~(1 << DDB3) & ~(1 << DDB2) & ~(1 << DDB1) & ~(1 << DDB0);
	DDRB |= (1 << DDB0);
	PORTB |= (1 << PB7) | (1 << PB6) | (1 << PB5) | (1 << PB4) | (1 << PB3) | (1 << PB2) | (1 << PB1) | (1 << PB0);
//PORT C			
	DDRC &= ~(1 << DDC7) & ~(1 << DDC6) & ~(1 << DDC5) & ~(1 << DDC4) & ~(1 << DDC3) & ~(1 << DDC2) & ~(1 << DDC1) & ~(1 << DDC0);
	PORTC |= (1 << PC7) | (1 << PC6) | (1 << PC5) | (1 << PC4) | (1 << PC3) | (1 << PC2) | (1 << PC1) | (1 << PC0);
//PORT D
	DDRD &= ~(1 << DDD7) & ~(1 << DDD6) & ~(1 << DDD5) & ~(1 << DDD4) & ~(1 << DDD3) & ~(1 << DDD2) & ~(1 << DDD1) & ~(1 << DDD0);
	PORTD |= (1 << PD7) | (1 << PD6) | (1 << PD5) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD1) | (1 << PD0);	
	return INIT_SUCCESS;
}