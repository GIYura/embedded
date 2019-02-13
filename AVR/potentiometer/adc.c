#include "adc.h"

extern uint16_t volt_adc;

void adc_ini(void){
	
	SET_BIT(ADCSRA, ADEN);
	SET_BIT(ADCSRA, ADIE);
	SET_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADMUX, REFS0);
} 

//------------------------------------------------------//
//					ADC HANDLER							//
//------------------------------------------------------//
ISR(ADC_vect){
	uint8_t sreg = SREG;
	volt_adc = ADCW;	
	SREG = sreg;
	SET_BIT(ADCSRA, ADSC);
}