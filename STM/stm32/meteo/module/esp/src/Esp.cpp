#include "Esp.h"
#include "Uart.h"

#include <stdint.h>
#include <stdio.h>

static Driver::Uart *uart = new Driver::Uart();

void espinit(void){

    if(NULL == uart){
	printf("Error. Can't create UART instance\n");
	return;
    }


    uart->init(Driver::Uart::UART_1, Driver::Uart::S_115200);
}