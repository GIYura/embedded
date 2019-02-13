
#include "uart.h" 
//--------------------------------------------------------------//
//						Õ¿—“–Œ… ¿ USART							//
//--------------------------------------------------------------//
void usart_ini(void)
{
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	SET_BIT(UCSRB, TXEN);
	SET_BIT(UCSRB, RXEN);
#ifdef USE_2X
	SET_BIT(UCSRA, U2X);
#else
	CLR_BIT(UCSRA, U2X);
#endif
}
//--------------------------------------------------------------//
//				‘”Õ ÷»ﬂ ¬€¬Œƒ¿ —»Ã¬ŒÀ¿ ¬ UART					//
//--------------------------------------------------------------//
int16_t usart_putchar(char c, FILE *stream)
{
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = c;
	return 0;
}

int16_t usart_getchar(FILE *stream)
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