//--------------------------------------------------------------//
//													            //
//--------------------------------------------------------------//
#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include <ctype.h>
//--------------------------------------------------------------//
//														        //
//--------------------------------------------------------------//
#define		INV_BIT(reg, bit)	reg ^= (1<<bit)
#define		LED_PIN				0
#define		SET_BIT(reg, bit)	reg |= (1<<bit)
#define		CLR_BIT(reg, bit)	reg &= (~(1<<bit))

//#define 	F_CPU				1000000
#define 	BAUD				9600
#include <util/setbaud.h>
#include <util/delay.h>
//------------------------------------ --------------------------//
//										                    	//
//--------------------------------------------------------------//
volatile uint8_t tmr_cntr = 10;
//--------------------------------------------------------------//
//						                						//
//--------------------------------------------------------------//
void port_init(void);
void usart_init(void);
void timer0_init(void);
int16_t usart_putchar(char c, FILE *stream);
int16_t usart_getchar(FILE *stream);

FILE usart_out = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE usart_input = FDEV_SETUP_STREAM(NULL, usart_getchar, _FDEV_SETUP_READ);
//--------------------------------------------------------------//
//						                						//
//--------------------------------------------------------------//
int main(void)
{
	port_init();
	usart_init();
	timer0_init();
	stdout = &usart_out;
	stdin = &usart_input;
	sei();

	printf("\r");
	#ifdef DEBUG
	printf("%s\r", "Debug version is running");
	#else
	printf("%s\r", "Release version is running");
	#endif

	printf("%s\r", "---------------------------");
	printf("%s\r", "+      Echo Program       +");
	printf("%s\r", "---------------------------");

    while(1)
    {
		printf("%s\r", "Press any key...");
		char symbol = getchar();
		if (bit_is_clear(UCSRA, FE) && bit_is_clear(UCSRA, DOR) && bit_is_clear(UCSRA, PE))
		{
			if (isdigit(symbol))
			{
				printf("%c%s\r", symbol, " - is digit");
			} else
			if (isalpha(symbol))
			{
				printf("%c%s\r", symbol, " - is alpha");
			}

			switch (symbol)
			{
				case 0x0d:
				printf("%s\r", "Entered symbol is: Enter");
				printf("------------------------\r");
				break;

				case ' ':
				printf("%s\r", "Entered symbol is: Space");
				printf("------------------------\r");
				break;

				default:
				printf("%s%c\r", "Entered symbol is: ", symbol);
				printf("------------------------\r");
				break;
			}
		} else
		{
			printf("%s\r", "Symbol was received with error");
		}
    }
}
//--------------------------------------------------------------//
//						                						//
//--------------------------------------------------------------//
void port_init(void)
{
	DDRB = 1; PORTB = 254;
}
//--------------------------------------------------------------//
//						            							//
//--------------------------------------------------------------//
void usart_init(void)
{
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	UCSRB |= 1<<TXEN | 1<<RXEN;
	#ifdef USE_2X
	UCSRA |= (1 << U2X);
	#else
	UCSRA &= ~(1 << U2X);
	#endif
}
//--------------------------------------------------------------//
//				                            					//
//--------------------------------------------------------------//
int16_t usart_putchar(char c, FILE *stream)
{
	if (c == '\n')
	{
		usart_putchar('\r', stream);
	}
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = c;
	return 0;
}
//--------------------------------------------------------------//
//				                            					//
//--------------------------------------------------------------//
int16_t usart_getchar(FILE *stream)
{
	loop_until_bit_is_set(UCSRA, RXC);
	return UDR;
}
//--------------------------------------------------------------//
//						                						//
//--------------------------------------------------------------//
void timer0_init(void)
{
/*
- Tt0 = k/Fcpu (k - 8,64,256,1024)
- n = 20 ìñ/Tt0
- TCNT0 = 256 - n
-----------------------------------------------------------------
CS02	CS01	CS00	Description
 0		 0		 0		No clock source (Timer/counter stopped).
 0 		 0 		 1		clkI/O/(No prescaling)
 0		 1		 0		clkI/O/8 (From prescaler)
 0		 1		 1		clkI/O/64 (From prescaler)
 1		 0		 0		clkI/O/256 (From prescaler)
 1		 0		 1		clkI/O/1024 (From prescaler)
 1		 1		 0		External clock source on T0 pin. Clock on falling edge.
 1		 1		 1		External clock source on T0 pin. Clock on rising edge.
 ----------------------------------------------------------------
 */
	TCCR0 = 1<<CS02;
	TCNT0 = 178;
	TIMSK = 1<<TOIE0;
}
//--------------------------------------------------------------//
//						                						//
//--------------------------------------------------------------//
ISR(TIMER0_OVF_vect)
{
	uint8_t sreg = SREG;
	TCNT0 = 178;
	tmr_cntr --;
	if (!tmr_cntr)
	{
		tmr_cntr = 10;
		INV_BIT(PORTB, LED_PIN);
	}
	SREG = sreg;
}
