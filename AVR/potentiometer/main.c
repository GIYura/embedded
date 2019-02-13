//--------------------------------------------------------------//
//						            							//
//--------------------------------------------------------------//
#include <stdlib.h>
#include <stdio.h>
#include "uart.h"
#include "periph_ini.h"
#include "adc.h"
//--------------------------------------------------------------//
//							        							//
//--------------------------------------------------------------//
//--------------------------------------------------------------//
//						                    					//
//--------------------------------------------------------------//
volatile uint16_t volt_adc = 0;
char buff[100];
//--------------------------------------------------------------//
//						                						//
//--------------------------------------------------------------//
FILE usart_out = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);
//--------------------------------------------------------------//
//						                						//
//--------------------------------------------------------------//
int main(void)
{
	stdout = &usart_out;
	port_ini();
	usart_ini();
	adc_ini();
	sei();
	SET_BIT(ADCSRA, ADSC);
	printf("%s\r", "--------------------------");
#ifdef DEBUG
	printf("%s\r", "Debug version is running");
#else
	printf("%s\r", "Release version is running");
#endif
	printf("%s\r", "--------------------------");
	//-----------------------ÄÈÑÏÅÒ×ÅÐ------------------------------//
	while(1)
	{
		double result = ((double)volt_adc * VREF)/(ADC_RESOLUTION - 1);
		printf("%s %s\r", "Voltage:", dtostrf(result, 6, 2, buff));
		INV_BIT(PORTB, LED_PIN);
		_delay_ms(500);
	}
	return 0;
}
