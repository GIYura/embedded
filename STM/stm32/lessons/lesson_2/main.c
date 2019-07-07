#include "stm32l1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void initGpio(void); 
void initClock(void);
void toggle(void);
void delay(uint32_t);
//
void main(void) {
    initClock();
    initGpio();
    while (1){
	toggle();
    }
}

//
void initGpio(void){
    GPIOC->MODER |= GPIO_MODER_MODER9_0 | GPIO_MODER_MODER8_0;		  //GPIO output mode (push-pull)
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9 | GPIO_OSPEEDER_OSPEEDR8;	  //speed (very high speed)
    GPIOC->PUPDR |= GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR8_0;		  //pull-up
}

//
void initClock(void){
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
}

//
void toggle(void){
//15:0 - set; 31:16 - reset
    GPIOC->BSRRH |= GPIO_BSRR_BS_9;
    GPIOC->BSRRL |= GPIO_BSRR_BS_8;	  
    delay(1000);
    GPIOC->BSRRL |= GPIO_BSRR_BS_9;
    GPIOC->BSRRH |= GPIO_BSRR_BS_8;
    delay(1000);
}

//
void delay(uint32_t d){
    //while(d--);
    vTaskDelay(d);
}


