#ifndef DEFS_H_
#define DEFS_H_
//---
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
#define I2C_CMD(x)					x
//---
#define  LED						0
//---
typedef enum
{
	INIT_SUCCESS = 0,
	INIT_FAILED
} T_INIT;
//---
typedef union
{
	struct
	{
		uint8_t gpioState		:	1;
		uint8_t uartState		:	1;
		uint8_t i2cState		:	1;
		uint8_t hwTimerState	:	1;
		uint8_t swTimerState	:	1;
		uint8_t fsmInitState	:	1;
		uint8_t					:	2;
	} bF;
	uint8_t commonSystemState;	
} T_systemState;
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
} T_BAUD_RATE;
//---
typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t ready;
} T_PCF_RAW_DATA;

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
} T_PCF_WR_DATA;

#endif /* DEFS_H_ */