#include "stm32l1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void vApplicationTickHook(void);

void initGpio(void); 
void initClock(void);
void vTaskToggle(void*);
void delay(uint32_t);
//
void main(void) {
    initClock();
    initGpio();

    xTaskCreate(vTaskToggle, "Led", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    while (1){
	
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
void vTaskToggle(void* arg){
//15:0 - set; 31:16 - reset
    for(;;){
	GPIOC->BSRRH |= GPIO_BSRR_BS_9;
	GPIOC->BSRRL |= GPIO_BSRR_BS_8;	  
	delay(100000);
	GPIOC->BSRRL |= GPIO_BSRR_BS_9;
	GPIOC->BSRRH |= GPIO_BSRR_BS_8;
	delay(100000);
    }

}

//
void delay(uint32_t d){
    while(d--);
    //vTaskDelay(d);
}

void vApplicationTickHook(void){

}


