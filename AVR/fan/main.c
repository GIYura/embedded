//--------------------------------------------------------------//
//						ÂÍÅØÍÈÅ ÔÀÉËÛ							//
//--------------------------------------------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "periph_ini.h"
#include "adc.h"
//--------------------------------------------------------------//
//							ÎÏÐÅÄÅËÅÍÈß							//
//--------------------------------------------------------------//
//--------------------------------------------------------------//
//						ÃËÎÁÀËÜÍÛÅ ÏÅÐÅÌÅÍÍÛÅ					//
//--------------------------------------------------------------//
//volatile uint16_t data_fan = 0;
volatile uint16_t volt_adc = 0;
char buff[100];
//--------------------------------------------------------------//
//						ÏÐÎÒÎÒÈÏÛ ÔÓÍÊÖÈÉ						//
//--------------------------------------------------------------//
/*ñîçäàíèå ïîòîêà usart_out òèïà FILE
íàçíà÷åíèå ôóíêöèè usart_putchar äëÿ âûâîäà â ïîòîê*/
FILE usart_output = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);
//FILE usart_input = FDEV_SETUP_STREAM(NULL, usart_getchar, _FDEV_SETUP_READ);
//--------------------------------------------------------------//
//						ÎÑÍÎÂÍÀß ÔÓÍÊÖÈß						//
//--------------------------------------------------------------//
int main(void)
{
    stdout = &usart_output;
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
		_delay_ms(500);
		INV_BIT(PORTB, LED_PIN);
//		cli();
//		data_fan *= 30;
//		printf("%s %u %s\r", "Fan speed:", data_fan, "RPM");
//		data_fan = 0;
//		sei();
//		printf("%s %u\r", "ADC code:", volt_adc);
		double result = ((double)volt_adc * VREF)/(ADC_RESOLUTION - 1);
		printf("%s %s\r", "Voltage:", dtostrf(result, 6, 2, buff));
		result = result * 20;
		printf("%s %u %c\r", "Fan load: ", (uint8_t)result, '%');
    }
}
