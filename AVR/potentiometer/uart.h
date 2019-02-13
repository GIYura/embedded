#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <avr/io.h>
#include "defs.h"
#include <util/setbaud.h>
#include <util/delay.h>

void usart_ini(void);
int16_t usart_putchar(char c, FILE *stream);

#endif /* UART_H_ */