/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 2014 - 2019 SEGGER Microcontroller GmbH             *
*                                                                    *
*           www.segger.com     Support: support@segger.com           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* conditions are met:                                                *
*                                                                    *
* - Redistributions of source code must retain the above copyright   *
*   notice, this list of conditions and the following disclaimer.    *
*                                                                    *
* - Neither the name of SEGGER Microcontroller GmbH                  *
*   nor the names of its contributors may be used to endorse or      *
*   promote products derived from this software without specific     *
*   prior written permission.                                        *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED.                                                        *
* IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR        *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : Generic application start

*/
#include <stdio.h>
#include <stdlib.h>

#include "stm32l1xx.h"
#include "stm32l1xx_usart.h"
/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/
void gpioInit(void);
void uartInit(void);
void uartSendChar(uint8_t data);
uint8_t uartGetChar(void);

void uartSendString(const char*);
char* uartGetString(void);

const char *message_1 = "Hello STM32";

void main(void) {
    
    gpioInit();
    uartInit();

    
    while (1){
        uartSendString(message_1);
        
        uartSendChar('\n');
        uartSendChar('\r');

        for(uint32_t i = 0; i < 700000; i++);
    }
}

void gpioInit(void){
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_InitTypeDef gpioCfg;
    gpioCfg.GPIO_Mode = GPIO_Mode_AF;
    gpioCfg.GPIO_OType = GPIO_OType_PP;
    gpioCfg.GPIO_Pin = GPIO_Pin_9;
    gpioCfg.GPIO_PuPd = GPIO_PuPd_UP;
    gpioCfg.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &gpioCfg);
}
//
void uartInit(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitTypeDef uartCfg;
    uartCfg.USART_BaudRate = 9600;
    uartCfg.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uartCfg.USART_Mode = USART_Mode_Tx;
    uartCfg.USART_Parity = USART_Parity_No;
    uartCfg.USART_StopBits = USART_StopBits_1;
    uartCfg.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &uartCfg);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

    USART_Cmd(USART1, ENABLE);

    USART_OverSampling8Cmd(USART1, ENABLE);
}

//
void uartSendChar(uint8_t data){
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, data);
}

//
uint8_t uartGetChar(void){
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData(USART1);
}

//
void uartSendString(const char* s){
    while(*s != 0)
    uartSendChar(*s++);
}

//
char* uartGetString(void){
    
    char *res = malloc(20);
    if(NULL == res){
        printf("Can't allocate memory\n");
    }
    char *t = res;
    char ch;
    while(ch = uartGetChar() != '\0'){
        *t++ = ch;
    }
    *t = '\0';
    return res;
}
/*************************** End of file ****************************/
