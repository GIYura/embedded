#include "periph_ini.h"
//--------------------------------------------------------------//
//						Õ¿—“–Œ… ¿ œŒ–“Œ¬						//
//--------------------------------------------------------------//
void port_ini(void)
{
	DDRB = 255; PORTB = 255;
//	SET_BIT(MCUCR, ISC01);							//The falling edge of INT0 generates an interrupt request
//	SET_BIT(GICR, INT0);							//External Interrupt Request 0 Enable
//	TCCR0 = 1<<CS02; TCNT0 = 178; TIMSK = 1<<TOIE0;	//20ms
	TCCR0 |= 1<<CS00;
	TCCR0 |= 1<<WGM01|1<<WGM00;
	TCCR0 |= 1<<COM01;
	OCR0 = 30;
}