#include "Uart.h"
#include "Ring.h"
#include "Fifo.h"
#include "stm32l1xx_usart.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_gpio.h"
#include <stdio.h>

#define RING_SIZE   256
#define FIFO_SIZE   256

static Lib::Ring *ring = new Lib::Ring(RING_SIZE);
static Lib::Fifo *fifo = new Lib::Fifo(FIFO_SIZE);
static uint8_t data;

Driver::Uart::Uart(){
    if(NULL == ring){
	printf("Error. Can't create Ring instance\n");
    }

    if(NULL == fifo){
	printf("Error. Can't create Fifo instance\n");
    }
    init(UART_0, S_115200);
}

Driver::Uart::~Uart(){

}

Driver::Uart::uart_state_t Driver::Uart::init(uart_number_t uN, uart_speed_t uS){
    if(uN >= UART_NUMBER){
	printf("Error. Unexpected UART number\n");
	return UART_FAILED;
    }

    if(uS >= S_NUMBER){
	printf("Error. Unexpected UART speed\n");
        return UART_FAILED;
    }

    uint32_t uartSpeed;

    switch(uS){
	case S_9600:
	    uartSpeed = 9600;
	break;

        case S_38400:
	    uartSpeed = 38400;
	break;

        case S_57600:
	    uartSpeed = 57600;
	break;

        case S_115200:
	    uartSpeed = 115200;
	break;
    }
    
    switch(uN){
	case UART_0:
	break;

        case UART_1:
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	    USART_InitTypeDef uartCfg;
	    uartCfg.USART_BaudRate		= uartSpeed;
	    uartCfg.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	    uartCfg.USART_Mode			= USART_Mode_Tx | USART_Mode_Rx;
	    uartCfg.USART_Parity		= USART_Parity_No;
	    uartCfg.USART_StopBits		= USART_StopBits_1;
	    uartCfg.USART_WordLength		= USART_WordLength_8b;
	    USART_Init(USART1, &uartCfg);
	    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	    USART_Cmd(USART1, ENABLE);
	    USART_OverSampling8Cmd(USART1, ENABLE);
	    NVIC_EnableIRQ(USART1_IRQn);
	break;

        case UART_2:
	break;
    }

    return UART_OK;
}

//
Driver::Uart::uart_state_t Driver::Uart::setBaudRate(uart_speed_t newSpeed){
    if(newSpeed >= S_NUMBER){
	printf("Error. Incorrect UART speed\n");
	return UART_FAILED;
    }
    return UART_OK;
}

//
void USART1_IRQHandler(void){
    
    if(USART_GetITStatus(USART1, USART_IT_TXE) == SET){
	USART_ClearFlag(USART1, USART_FLAG_TXE);
//pop data from ring and send via uart
	fifo->pop(&data);
	USART_SendData(USART1, data);
    }

    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET){
	USART_ClearFlag(USART1, USART_FLAG_RXNE);
//receive data from uart and push to ring
	data = (uint8_t)USART_ReceiveData(USART1);
	ring->push(data);
    }

//over run error
    if(USART_GetITStatus(USART1, USART_IT_ORE) == SET){
	USART_ClearFlag(USART1, USART_FLAG_ORE);

    }

//frame error
    if(USART_GetITStatus(USART1, USART_IT_FE) == SET){ 
	USART_ClearFlag(USART1, USART_FLAG_FE);

    }

//parity error
    if(USART_GetITStatus(USART1, USART_IT_PE) == SET){
	USART_ClearFlag(USART1, USART_FLAG_PE);

    }


}