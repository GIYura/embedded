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
#include <stdbool.h>
#include <string.h>

#include "stm32l1xx.h"
#include "stm32l1xx_usart.h"
/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/
#define LED_GREEN     GPIO_Pin_9

void sysClockInit(void);
void gpioInit(void);
void uartInit(void);
void uartSendChar(uint8_t data);
uint8_t uartGetChar(void);

void uartSendString(const char*);
char* uartGetString(void);

const char *message_1 = "Hello STM32 from Segger";

//
typedef enum{
    EXPIRED = 0,
    UNEXPIRED
}SW_TIMER_STATE; 

typedef enum{
    SW_TIMER_0,
    SW_TIMER_1,
    SW_TIMER_2,
    SW_TIMER_3,
    SW_TIMER_4,
    SW_TIMER_5,
    SW_TIMER_6,
    SW_TIMER_NUMBER
}SW_TIMER_IDX; 

typedef struct{
  bool        active;
  SW_TIMER_IDX  numer;
  uint32_t    ticks;
}timer_t;

timer_t swTimer[SW_TIMER_NUMBER];

void swTimerInit();
void swTimerEnable(SW_TIMER_IDX,uint32_t);
void swTimerDisable(SW_TIMER_IDX);
bool isSwTimerExpired(SW_TIMER_IDX);
void swTimerProcess(void);
//
//
//
void main(void){
    
    //sysClockInit();
    gpioInit();
    //uartInit();
    //swTimerInit();
    
    while (1){
        /*swTimerEnable(SW_TIMER_0, 1000);
        if(isSwTimerExpired(SW_TIMER_0) == EXPIRED){
            swTimerDisable(SW_TIMER_0);
            swTimerEnable(SW_TIMER_0, 1000);
            uartSendString(message_1);
            uartSendChar('\n');
            uartSendChar('\r');
        }
        swTimerEnable(SW_TIMER_1, 500);
        if(isSwTimerExpired(SW_TIMER_1) == EXPIRED){
            swTimerDisable(SW_TIMER_1);
            swTimerEnable(SW_TIMER_1, 500);
            GPIO_ToggleBits(GPIOC, LED_GREEN);
        }*/
    }
}

//
void sysClockInit(void){
    SysTick_Config(SystemCoreClock / 1000);
}

//
void gpioInit(void){

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA /*| RCC_AHBPeriph_GPIOC*/, ENABLE);
    GPIO_InitTypeDef gpioCfg;
/*    gpioCfg.GPIO_Mode = GPIO_Mode_AF;
    gpioCfg.GPIO_OType = GPIO_OType_PP;
    gpioCfg.GPIO_Pin = GPIO_Pin_9;
    gpioCfg.GPIO_PuPd = GPIO_PuPd_UP;
    gpioCfg.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &gpioCfg);

    memset(&gpioCfg, 0, sizeof(GPIO_InitTypeDef));

    gpioCfg.GPIO_Pin = LED_GREEN;
    gpioCfg.GPIO_Mode = GPIO_Mode_OUT;
    gpioCfg.GPIO_OType = GPIO_OType_PP;
    gpioCfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpioCfg.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &gpioCfg);
*/
    gpioCfg.GPIO_Mode = GPIO_Mode_AF;
    gpioCfg.GPIO_OType = GPIO_OType_PP;
    gpioCfg.GPIO_Pin = GPIO_Pin_8;
    gpioCfg.GPIO_PuPd = GPIO_PuPd_UP;
    gpioCfg.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &gpioCfg);
    
    RCC->CFGR |= (1 << 24) | (1 << 26);// | (1 << 24) ;
    //IS_RCC_MCO_SOURCE(RCC_MCOSource_SYSCLK);
//(bit 24) sysclock - 16MHz
//(bit 25) HSI - 
//(bit 24, 25) MSI - 2MHz
//(bit 26) HSE - 4MHz
//(bit 24, 26) PLL - 16 MHz
//(bit 26, 25) LSI - 
//(bit 26, 25, 24) LSE - 

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

//
void swTimerInit(){
    for(SW_TIMER_IDX idx = SW_TIMER_0; idx < SW_TIMER_NUMBER; idx++){
        swTimer[idx].active = false;
        swTimer[idx].numer = SW_TIMER_NUMBER;
        swTimer[idx].ticks = 0;
    }
}

//
void swTimerEnable(SW_TIMER_IDX idx,uint32_t nTicks){
    if(idx < SW_TIMER_0 || idx > SW_TIMER_6){
        return;
    }
    if(!swTimer[idx].active){
         swTimer[idx].active = true;
         swTimer[idx].numer = idx;
         swTimer[idx].ticks = nTicks;
    }
} 

//
void swTimerDisable(SW_TIMER_IDX idx){
    if(idx < SW_TIMER_0 || idx > SW_TIMER_6){
        return;
    }
    if(swTimer[idx].active){
        swTimer[idx].active = false;
        swTimer[idx].numer = SW_TIMER_NUMBER;
        swTimer[idx].ticks = 0;
    }
}

//
bool isSwTimerExpired(SW_TIMER_IDX idx){
    if(idx < SW_TIMER_0 || idx > SW_TIMER_6){
        return false;
    }
    if(swTimer[idx].active && swTimer[idx].ticks == 0){
        return EXPIRED;
    } else {
        return UNEXPIRED;
    }
}

//
void swTimerProcess(void){
    for(SW_TIMER_IDX idx = SW_TIMER_0; idx < SW_TIMER_NUMBER; idx++){
        if(swTimer[idx].active && swTimer[idx].ticks != 0){
            swTimer[idx].ticks--;
        }
    }
}

//
void SysTick_Handler(void){
    swTimerProcess();
}
/*************************** End of file ****************************/
