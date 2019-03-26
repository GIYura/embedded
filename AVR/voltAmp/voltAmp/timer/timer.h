#ifndef TIMER_H_
#define TIMER_H_


#include "../definitions/defs.h"

typedef enum
{
	SW_TIMER0 = 0,
	SW_TIMER1,
	SW_TIMER2,
	SW_TIMER_NUMBER,
	SW_TIMER_OFR = 255
} SW_TIMER_IDX;

typedef enum
{
	SW_TIMER_EXPIRED = 0,
	SW_TIMER_UNEXPIRED
} SW_TIMER_STATE;


uint8_t hwTimerInit(uint8_t aRequiredPeriodInterrupt);
uint8_t swTimerInit(SW_TIMER_IDX aTimer0, SW_TIMER_IDX aTimer1, SW_TIMER_IDX aTimer2);
SW_TIMER_IDX enableSwTimer(SW_TIMER_IDX aSwTimerNumber, uint8_t aTicksNumber);
SW_TIMER_IDX disableSwTimer(SW_TIMER_IDX aSwTimerNumber);
SW_TIMER_STATE isSwTimeout(SW_TIMER_IDX aSwTimerNumber);
void swTimerProcess(void);


#endif /* TIMER_H_ */