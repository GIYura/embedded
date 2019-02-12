
#include "uart.h" 
//--------------------------------------------------------------//
//						мюярпнийю USART							//
//--------------------------------------------------------------//
void usart_ini(void)
{
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	SET_BIT(UCSRB, TXEN);
	#ifdef USE_2X
	SET_BIT(UCSRA, U2X);
	#else
	CLR_BIT(UCSRA, U2X);
	#endif
}
//--------------------------------------------------------------//
//				тсмйжхъ бшбндю яхлбнкю б UART					//
//--------------------------------------------------------------//
int16_t usart_putchar(char c, FILE *stream)
{
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = c;
	return 0;
}