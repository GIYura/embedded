//---------------------------------------------------------------//
/*
Description	: Real time clock
uC			: ATmega32
clock		: pcf8535
*/
//---------------------------------------------------------------//
#include "main.h"
FILE usartOutput = FDEV_SETUP_STREAM(usartPutChar, NULL, _FDEV_SETUP_WRITE);
FILE usartInput = FDEV_SETUP_STREAM(NULL, usartGetChar, _FDEV_SETUP_READ);
T_systemState systemState = {{1,1,1,1,1,1}};
T_PCF_RAW_DATA pcfRawData = {0,0,0,0};
T_PCF_WR_DATA pcfWrData = {0,0,0};
	
//****
#define IN_BUFF_SZ 20	
char inBuff[IN_BUFF_SZ];
void receiveBuff(char *buff);
//---------------------------------------------------------------//
//
//---------------------------------------------------------------//
int main(void)
{
	stdout = &usartOutput;
	stdin = &usartInput;
//---
	systemState.bF.fsmInitState = fsmInit();	
	systemState.bF.gpioState = gpioInit();
	systemState.bF.uartState = usartInit(S_9600);								//9600 bit/s
	systemState.bF.i2cState = i2cInit();
	systemState.bF.hwTimerState = hwTimerInit(20);								//20 ms
	systemState.bF.swTimerState = swTimerInit(SW_TIMER0, SW_TIMER1, SW_TIMER2);
//---	
	if (systemState.commonSystemState == 0)
	{
		printf("%s\r", "--------------------------------");
		printf("%s\r", "|       INIT SUCCESS           |");
		printf("%s\r", "--------------------------------");	
	} 
	else
	{
		for (;;)
		{
			printf("INIT FAILED. Error Code %xh\r", systemState.commonSystemState);
			_delay_ms(1000);
		}
	}	
	sei();
//-----------------------------------------------------------------------------------------//
//										DISPATCHER
//-----------------------------------------------------------------------------------------//
    while(1)
    {	
/*		fsmProcess(fsmRun(), &pcfRawData);
		pcfConvertRawData(&pcfRawData);
//---LED blinking	
		enableSwTimer(SW_TIMER2, 10);
		if (isSwTimeout(SW_TIMER2) == SW_TIMER_EXPIRED)
		{
			disableSwTimer(SW_TIMER2);
			PORTB ^= (1 << LED);
			enableSwTimer(SW_TIMER2, 10);
		}
//---
*/

		receiveBuff(inBuff);
		for (uint8_t i = 0; i < IN_BUFF_SZ - 1; i++)
		{
			printf("buff[%d]:%c\r", i, inBuff[i]);
		}

		printf("Received sequence:%s\r", inBuff);//fgets(inBuff, 10, stdin));
		convertASCII_2_BCD(inBuff, &pcfWrData);
		printf("Data to write:\r");
		printf("sec: %d\r", pcfWrData.sec);
		printf("min: %d\r", pcfWrData.min);
		printf("hour: %d\r", pcfWrData.min);
		_delay_ms(500);
	}
}

void receiveBuff(char *buff)
{
	char c;
	uint8_t i = 0;
	
	while (i < IN_BUFF_SZ - 1)
	{
		c = getchar();
		if (c == 0x0d)
		{
			break;
		}
		inBuff[i] = c;	
		i++;	
	}
	inBuff[i] = '\n';
}