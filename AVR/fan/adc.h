#ifndef ADC_H_
#define ADC_H_

//#include <avr/io.h>
#include <avr/interrupt.h>
#include "defs.h"

void adc_ini(void);
ISR(ADC_vect);


#endif /* ADC_H_ */