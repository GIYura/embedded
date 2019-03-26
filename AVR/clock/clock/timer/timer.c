#include "timer.h"

typedef enum
{
	SW_TIMER_DISABLE = 0,
	SW_TIMER_ENABLE
} SW_TIMER_MODE;

#pragma pack(push, 1)
typedef struct
{
	uint8_t	state			:	1;
	SW_TIMER_IDX number;
	uint16_t tNumber;
} TswTimer;
#define T_SW_TIMER_SZ sizeof(TswTimer)
#pragma pack(pop)

TswTimer swTimer[SW_TIMER_NUMBER];

//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
T_INIT hwTimerInit(uint8_t aRequiredPeriodInterrupt)
{
#define TIMER_RESOLUTION	8
/*
PRESCALER = 256
f0 (Дастота тикани§ таймера) = F_CPU/prescaler = 3.9 kHz = 3900 Hz
t0 (Уребуемый интервал) = 20 ms (20*10^-3)
t1 = t0 * f = (20*10^-3) * 3.9*10^3 = 78
TCNT0 = 256 - t1 = 256 - 78 = 178
*/
	uint16_t hwTimerFreq = F_CPU / 256;
	uint8_t valueTCNT0 = ( pow(2, TIMER_RESOLUTION) - (((aRequiredPeriodInterrupt * 0.1) * hwTimerFreq) * 0.01)) + 1;

	TCCR0 |= (1 << CS02);
	TCNT0 = valueTCNT0;
	TIMSK |= (1 << TOIE0);

	return INIT_SUCCESS;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
T_INIT swTimerInit(SW_TIMER_IDX aTimer0, SW_TIMER_IDX aTimer1, SW_TIMER_IDX aTimer2)
{
	if (	(aTimer0 < SW_TIMER0) || (aTimer0 > SW_TIMER2)	||
			(aTimer1 < SW_TIMER0) || (aTimer1 > SW_TIMER2)	||
			(aTimer2 < SW_TIMER0) || (aTimer2 > SW_TIMER2)
	)
	{
		return INIT_FAILED;
	}
	swTimer[SW_TIMER0].number = aTimer0;
	swTimer[SW_TIMER1].number = aTimer1;
	swTimer[SW_TIMER2].number = aTimer2;
	return INIT_SUCCESS;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
SW_TIMER_IDX enableSwTimer(SW_TIMER_IDX aSwTimerNumber, uint8_t aTicksNumber)
{
	cli();
	if ( (aSwTimerNumber < SW_TIMER0) || (aSwTimerNumber > SW_TIMER2) || swTimer[aSwTimerNumber].state == SW_TIMER_ENABLE)
	{
		sei();
		return INIT_FAILED;
	}
	swTimer[aSwTimerNumber].state = SW_TIMER_ENABLE;
	swTimer[aSwTimerNumber].tNumber = aTicksNumber;
	sei();
	return aSwTimerNumber;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
SW_TIMER_IDX disableSwTimer(SW_TIMER_IDX aSwTimerNumber)
{
	cli();
	if ( (aSwTimerNumber < SW_TIMER0) || (aSwTimerNumber > SW_TIMER2) )
	{
		sei();
		return INIT_FAILED;
	}
	swTimer[aSwTimerNumber].state = SW_TIMER_DISABLE;
	swTimer[aSwTimerNumber].tNumber = 0;
	sei();
	return aSwTimerNumber;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
SW_TIMER_STATE isSwTimeout(SW_TIMER_IDX aSwTimerNumber)
{
	cli();
	if ( (aSwTimerNumber < SW_TIMER0) || (aSwTimerNumber > SW_TIMER2))
	{
		sei();
		return SW_TIMER_OFR;
	}

	if (swTimer[aSwTimerNumber].tNumber == 0)
	{
		sei();
		return SW_TIMER_EXPIRED;
	}
	else
	{
		sei();
		return SW_TIMER_UNEXPIRED;
	}
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
void swTimerProcess(void)
{
	for (uint8_t i = 0; i < SW_TIMER_NUMBER; i++)
	{
		if ( (swTimer[i].state == SW_TIMER_ENABLE) && (swTimer[i].tNumber != 0) )
		{
			swTimer[i].tNumber--;
		}
	}
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
ISR(TIMER0_OVF_vect)
{
	cli();
	uint8_t sreg = SREG;
	TCNT0 = 178;
	swTimerProcess();
	SREG = sreg;
	sei();
} 
