#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>

#undef		F_CPU
#define 	F_CPU				1000000L
#define 	BAUD				9600L
#define		SET_BIT(reg, bit)	reg |= (1<<bit)
#define		CLR_BIT(reg, bit)	reg &= (~(1<<bit))

#include <util/setbaud.h>


void usart_ini(void);
int16_t usart_putchar(char c, FILE *stream);

#endif /* UART_H_ */