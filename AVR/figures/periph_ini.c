#include "periph_ini.h"
//--------------------------------------------------------------//
//						Õ¿—“–Œ… ¿ œŒ–“Œ¬						//
//--------------------------------------------------------------//
void port_ini(void)
{
	DDRB = 1; PORTB = 254;
	SET_BIT(MCUCR, ISC01);							//The falling edge of INT0 generates an interrupt request
	SET_BIT(GICR, INT0);							//External Interrupt Request 0 Enable
	TCCR0 = 1<<CS02; TCNT0 = 178; TIMSK = 1<<TOIE0;	//20ms
}