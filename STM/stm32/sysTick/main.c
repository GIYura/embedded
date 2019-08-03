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
#include "stm32l1xx.h"

#include <stdbool.h>
/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/
#define LED_GREEN   GPIO_Pin_9
#define LED_BLUE    GPIO_Pin_8

#define  F_CPU    72000000UL
#define  TIMER_F  F_CPU/10 - 1

void task_blink_led_green(void);
void task_blink_led_blue(void);

typedef enum{
    INACTIVE = 0,
    ACTIVE
}timer_state_t; 

typedef enum{
    TIMER0 = 0,
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
    TIMER_NUMBER
}timer_number_t; 

typedef struct{
    uint8_t active;
    uint32_t ticks;
    void (*callback)(void);
}timer_t;

void timer_enable(timer_number_t, uint32_t);
void timer_disable(timer_number_t);
bool is_timeout(timer_number_t);
void timer_process();

static timer_t sw_timer[TIMER_NUMBER] = {  
					  INACTIVE, 0, task_blink_led_blue,
					  INACTIVE, 0, task_blink_led_green
					};
//
void main(void) {
    GPIO_InitTypeDef gpioInit;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

    gpioInit.GPIO_Mode = GPIO_Mode_OUT;
    gpioInit.GPIO_OType = GPIO_OType_PP;
    gpioInit.GPIO_Pin = LED_BLUE | LED_GREEN;
    gpioInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpioInit.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &gpioInit);

    GPIO_SetBits(GPIOC, LED_BLUE);
    GPIO_ResetBits(GPIOC, LED_GREEN);

    SysTick_Config(TIMER_F);

    timer_enable(TIMER0, 1);
    timer_enable(TIMER1, 1);

    while(1){

    }
}

void SysTick_Handler(){
    timer_process();
}
/*************************** End of file ****************************/
void timer_enable(timer_number_t t, uint32_t time){
    if(sw_timer[t].active == INACTIVE){
	sw_timer[t].active = ACTIVE;
	sw_timer[t].ticks = time;
    }
}

void timer_disable(timer_number_t t){
    if(sw_timer[t].active == ACTIVE){
	sw_timer[t].active = INACTIVE;
	sw_timer[t].ticks = 0;
    }
}

bool is_timeout(timer_number_t t){
    if(sw_timer[t].active == ACTIVE){
	if(sw_timer[t].ticks == 0){
	    return true;
	} else {
	    return false;
	}
    }
    return false;
}


void timer_process(){
    for(uint8_t i = 0; i < TIMER_NUMBER; i++){
	if(sw_timer[i].active == ACTIVE){
	    if(is_timeout(i)){
		sw_timer[i].callback();
	    } else {
		sw_timer[i].ticks--;
	    }
	}
    }
}

void task_blink_led_green(void){
    GPIO_ToggleBits(GPIOC, LED_GREEN);
}

void task_blink_led_blue(void){
    GPIO_ToggleBits(GPIOC, LED_BLUE);
}