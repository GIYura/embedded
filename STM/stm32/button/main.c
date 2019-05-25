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

#define LED_GREEN     GPIO_Pin_9
#define LED_BLUE      GPIO_Pin_8
#define BUTTON        GPIO_Pin_0
static uint8_t counter = 0;
uint8_t flag = 0;
/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/
void main(void) {
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  GPIO_InitTypeDef gpioInit, buttonInit;

//led settings
  gpioInit.GPIO_Mode = GPIO_Mode_OUT;
  gpioInit.GPIO_OType = GPIO_OType_PP;
  gpioInit.GPIO_Pin = LED_BLUE | LED_GREEN;
  gpioInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
  gpioInit.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &gpioInit);

//button settings
  buttonInit.GPIO_Mode = GPIO_Mode_IN;
  buttonInit.GPIO_OType = GPIO_OType_OD;
  buttonInit.GPIO_Pin = BUTTON;
  buttonInit.GPIO_PuPd = GPIO_PuPd_DOWN;
  buttonInit.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &buttonInit);

  GPIO_ResetBits(GPIOC, LED_BLUE);
  GPIO_ResetBits(GPIOC, LED_GREEN);

  while (1){
      if((GPIO_ReadInputDataBit(GPIOA, BUTTON) == Bit_SET) && (flag == 0)){
          counter++;
          flag = 1;
      }

      switch(counter){
          case 1:
              GPIO_SetBits(GPIOC, LED_GREEN);
              //GPIO_ResetBits(GPIOC, LED_BLUE);
              flag = 0;
          break;

          case 2:
              GPIO_SetBits(GPIOC, LED_BLUE);
              //GPIO_ResetBits(GPIOC, LED_GREEN);
              flag = 0;
          break;

          case 3:
              GPIO_ResetBits(GPIOC, LED_GREEN);
              //GPIO_SetBits(GPIOC, LED_BLUE);
              flag = 0;
          break;

          case 4:
              GPIO_ResetBits(GPIOC, LED_BLUE);
              //GPIO_SetBits(GPIOC, LED_GREEN);
              counter = 0;
              flag = 0;
          break;
      }
  }
}

/*************************** End of file ****************************/
