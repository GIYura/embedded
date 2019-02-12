#ifndef DS18B20_H_
#define DS18B20_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

//setup connection
#define DS18B20_PORT				PORTC
#define DS18B20_DDR					DDRC
#define DS18B20_PIN					PINC
#define DS18B20_DQ					PC7//PC0

#define THERM_INPUT_MODE			DS18B20_DDR &= ~(1<<DS18B20_DQ)
#define THERM_OUTPUT_MODE			DS18B20_DDR |= (1<<DS18B20_DQ)
#define THERM_LOW					DS18B20_PORT &= ~(1<<DS18B20_DQ)
#define THERM_HIGH					DS18B20_PORT |= (1<<DS18B20_DQ)

//commands
#define DS18B20_CMD_CONVERTTEMP		0x44
#define DS18B20_CMD_RSCRATCHPAD		0xbe
#define DS18B20_CMD_WSCRATCHPAD		0x4e
#define DS18B20_CMD_CPYSCRATCHPAD	0x48
#define DS18B20_CMD_RECEEPROM		0xb8
#define DS18B20_CMD_RPWRSUPPLY		0xb4
#define DS18B20_CMD_SEARCHROM		0xf0
#define DS18B20_CMD_READROM			0x33
#define DS18B20_CMD_MATCHROM		0x55
#define DS18B20_CMD_SKIPROM			0xcc
#define DS18B20_CMD_ALARMSEARCH		0xec

//stop any interrupt on read
#define DS18B20_STOPINTERRUPTONREAD	1

//functions
double ds18b20_gettemp();

#endif
