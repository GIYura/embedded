#ifndef DEFS_H_
#define DEFS_H_
//---------------------------------------------------------------------//
#include <inttypes.h>								//
#include <avr/io.h>									//
#include <avr/sfr_defs.h>							//
#include <stdio.h>									//
#include <string.h>									//
#include <avr/interrupt.h>							//
#include <stdbool.h>								//
#include <stdlib.h>
//---
#ifndef	F_CPU
#undef	F_CPU
#define	F_CPU						1000000UL		//
#endif
#include <util/delay.h>
//---
#define	INIT_SUCCESS				0				//
#define	INIT_FAILED					1				//
//---
#define VREF_2_5					0				//
#define VREF_5_0					1				//
//

#define SEND_2_TERMINAL
#define LED_BLINK
#define LED							PC5

#pragma pack(push, 1)
//---
typedef union
{
	struct
	{
		uint8_t uartState		:	1;
		uint8_t gpioState		:	1;
		uint8_t lcdState		:	1;
		uint8_t adcInit			:	1;
		uint8_t hwTimerState	:	1;
		uint8_t swTimerState	:	1;
		uint8_t 				:	2;	
	} bF;	
	uint8_t commonSystemState;
} TsystemState;
#define T_SYSTEM_STATE_SZ sizeof(TsystemState)
//---
typedef struct
{
	uint16_t resolution;
	double vRef;
	double rDividerCoeffV;
	double rDividerCoeffA;
	double amplifierCoeff;
} TadcCoeff;
#define  T_ADC_COEFF_SZ sizeof(TadcCoeff)
#pragma pack(pop)
//---
typedef enum
{
	S_2400 = 0,
	S_4800,
	S_9600,
	S_14400,
	S_19200,
	S_28800,
	S_38400,
	S_57600,
	S_76800,
	S_115200,
	BAUDRATE_NUMBER
} TbaudRate;
//---------------------------------------------------------------------//
#endif /* DEFS_H_ */