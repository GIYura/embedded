/*-----------------------------------------------------------------------------------------//
Программа функционирования вольтмерта-амперметра.
-------------------------------------------------------------------------------------------
Контроллер:		ATmega8
Частота:		1MHz
Скорость:		9600 bit/s
Pinouts:
PB0 - RS
PB1 - RW
PB2 - E
PB3 - 
PB4 - D4
PB5 - D5
PB6 - D6
PB7 - D7
PC0(ADC0) - VOLTAGE
PC1(ADC1) - CURRENT
-----------------------------------------------------------------------------------------//*/
#include "main.h"
static TsystemState systemState = {{1,1,1,1,1,1}};
static TadcCoeff adcCoeff;
static char buff[10] = {0};
//-----------------------------------------------------------------------------------------//
FILE usart_output = FDEV_SETUP_STREAM(usartPutChar, NULL, _FDEV_SETUP_WRITE);
FILE lcd_output = FDEV_SETUP_STREAM(lcdPrintChar, NULL, _FDEV_SETUP_WRITE);
//-----------------------------------------------------------------------------------------//
//										MAIN
//-----------------------------------------------------------------------------------------//
int main(void)
{
	stderr = &usart_output;
	stdout = &lcd_output;
	
	systemState.bF.uartState = usartInit(S_9600);
	systemState.bF.gpioState = gpioInit();
	systemState.bF.lcdState = lcdInit();
	systemState.bF.adcInit = adcInit(VREF_5_0, &adcCoeff);
	systemState.bF.hwTimerState = hwTimerInit(20);		//20ms
	systemState.bF.swTimerState = swTimerInit(SW_TIMER0, SW_TIMER1, SW_TIMER2);
	
	if (systemState.commonSystemState == 0)
	{
		fprintf(stderr, "-----------------\r");
		fprintf(stderr, "   INIT SUCCESS  \r");
		fprintf(stderr, "-----------------\r");
	}
	else
	{
		for (;;)
		{
			fprintf(stderr, "INIT FAILED. Error Code %xh\r", systemState.commonSystemState);
			_delay_ms(1000);
		}
	}
//-----
	lcdSetCursor(0, 0);
	fprintf(stdout, "V");
	fprintf(stdout, ":");
	fprintf(stdout, "9");
	fprintf(stdout, "9");
	fprintf(stdout, ",");
	fprintf(stdout, "9");
	fprintf(stdout, "9");
	fprintf(stdout, "U");
//-----	
	lcdSetCursor(1, 0);
	fprintf(stdout, "C");
	fprintf(stdout, ":");
	fprintf(stdout, "9");
	fprintf(stdout, "9");
	fprintf(stdout, ",");
	fprintf(stdout, "9");
	fprintf(stdout, "9");
	fprintf(stdout, "A");
//-----
	sei();
//-----------------------------------------------------------------------------------------//
//										DISPATCHER
//-----------------------------------------------------------------------------------------//
     while (1) 
    {
//-----200 ms dislpay				
		enableSwTimer(SW_TIMER1, 10);
		if (isSwTimeout(SW_TIMER1) == SW_TIMER_EXPIRED)
		{
			disableSwTimer(SW_TIMER1);
			enableSwTimer(SW_TIMER1, 10);
			uint16_t voltageL = ((((double)adcCodeProcess(getVoltageCode()) * adcCoeff.vRef) * adcCoeff.rDividerCoeffV) / 1024) * 1000;
			//uint16_t currentL = (((((double)adcCodeProcess(getCurrentCode()) * adcCoeff.vRef) * adcCoeff.rDividerCoeffA) / 1.024)) / adcCoeff.amplifierCoeff;
			lcdPrintData(0, 2, voltageL);
			//lcdPrintData(1, 3, currentL);
		}
//-----1000 ms send to terminal
#ifdef SEND_2_TERMINAL
		enableSwTimer(SW_TIMER0, 100);
		if (isSwTimeout(SW_TIMER0) == SW_TIMER_EXPIRED)
		{
			disableSwTimer(SW_TIMER0);
			enableSwTimer(SW_TIMER0, 100);
			double voltageT = (((double)adcCodeProcess(getVoltageCode()) * adcCoeff.vRef) * adcCoeff.rDividerCoeffV) / adcCoeff.resolution;
			fprintf(stderr, "Voltage = %s %c\r", dtostrf(voltageT, 4, 2, buff), 'V');
			//double currentT = ((((double)adcCodeProcess(getCurrentCode()) * adcCoeff.vRef) * adcCoeff.rDividerCoeffA) / adcCoeff.resolution) / adcCoeff.amplifierCoeff;
			//fprintf(stderr, "Current = %s %c\r", dtostrf(currentT, 4, 2, buff), 'A');
			fprintf(stderr, "-----------------\r");
		}
//-----
#endif

#ifdef LED_BLINK
		enableSwTimer(SW_TIMER2, 25);
		if (isSwTimeout(SW_TIMER2) == SW_TIMER_EXPIRED)
		{
			disableSwTimer(SW_TIMER2);
			enableSwTimer(SW_TIMER2, 25);
			PORTC ^= (1 << LED);
		}
#endif
    }
}