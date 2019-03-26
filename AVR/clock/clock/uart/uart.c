#include "uart.h"
//-----------------------------------------------------------------------------------------//
volatile const uint32_t bRate[BAUDRATE_NUMBER] = {	2400,
													4800,
													9600,
													14400,
													19200,
													28800,
													38400,
													57600,
													76800,
													115200
												};
//-----------------------------------------------------------------------------------------//
//									ÍÀÑÒĞÎÉÊÀ USART										//
//-----------------------------------------------------------------------------------------//

T_INIT usartInit(T_BAUD_RATE aBr)
{
	if (aBr > S_115200)
	{
		return INIT_FAILED;
	}
	
	uint32_t baudRate = (F_CPU/(8L * bRate[aBr]) - 1);
	
	UBRRL = baudRate;
	UBRRH = baudRate >> 8;

//transmitter - enable; receiver - enable; rx compete interrupt enable
	UCSRB = (1 << TXEN) | (1 << RXEN);// | (1 << RXCIE) | (1 << TXCIE);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UCSRA = (1 << U2X);							//double speed
	
	return INIT_SUCCESS;
}
//-----------------------------------------------------------------------------------------//
//							ÔÓÍÊÖÈß ÂÛÂÎÄÀ ÑÈÌÂÎËÀ Â UART								//
//-----------------------------------------------------------------------------------------//
int16_t usartPutChar(char c, FILE *stream)
{
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = c;
	return 0;
}
//-----------------------------------------------------------------------------------------//
//							ÔÓÍÊÖÈß ÂÂÂÎÄ ÑÈÌÂÎËÀ Â UART								//
//-----------------------------------------------------------------------------------------//
int16_t usartGetChar(FILE *stream)
{
	loop_until_bit_is_set(UCSRA, RXC);
	if (bit_is_set(UCSRA, FE) || bit_is_set(UCSRA, DOR) || bit_is_set(UCSRA, PE))
	{ 
		return UDR = 0;
	}
	else 
	{ 
		return UDR;
	}
}