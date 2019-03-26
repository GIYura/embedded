#ifndef UART_H_
#define UART_H_
//-----------------------------------------------------------------------------------------//
#include "../definitions/defs.h"
//-----------------------------------------------------------------------------------------//
uint8_t usartInit(TbaudRate aBr);
int16_t usartPutChar(char c, FILE *stream);
int16_t usartGetChar(FILE *stream);
//-----------------------------------------------------------------------------------------//
#endif /* UART_H_ */