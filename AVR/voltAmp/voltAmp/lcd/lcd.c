#include "lcd.h"
/*
PIN		SIGNAL		LEVEL
--------------------------
1		GND			0
2		VCC			+5V
3		Vo			LCD brightness
4		RS			H: data; L: instruction
5		R/W			H: read; L: write
6		E			H->L chip enable signal
7		D0			
8		D1
9		D2
10		D3
11		D4
12		D5
13		D6
14		D7
*/
#define LCD_RS					PB0
#define LCD_RW					PB1
#define LCD_E					PB2
#define LCD_D4					PB4
#define LCD_D5					PB5
#define LCD_D6					PB6
#define LCD_D7					PB7 

#define LCD_PORT_DIR			DDRB
#define LCD_PORT_STATE			PORTB
#define BUSY_FLAG				7

#define BLINKING				(1 << 0)
#define CURSOR					(1 << 1)
#define DISPLAY					(1 << 2)

#define NO_BLINKING				(~(1 << 0))
#define NO_CURSOR				(~(1 << 1))
#define NO_DISLAY				(~(1 << 2))

#define LCD_ON_OFF_CONTROL(x)	(1 << 3) | (x)

#define FONT					2
#define LINE_NUMBER				3
#define DATA_LENGTH				4
#define LCD_FUNCTION_SET(x)		(1 << 5) | (x)

#define LCD_CLEAR				(1 << 0)

#define SHIFT					0
#define INCREMENT				1
#define LCD_ENTRY_MODE_SET(x)	(1 << 2) | (x)	

#define LCD_SET_DDRAM(x)		(1 << 7) | (x)

typedef enum
{
	INPUT = 0,
	OUTPUT	
} LCD_DATA_PORT_DIR;

typedef enum
{
	WRITE = 0,	
	READ
} LCD_MODE;

typedef enum
{
	INSTRUCTION = 0,
	DATA
} LCD_REGS;

//void lcdPrintChar(uint8_t aChar);
//uint16_t lcdPrintChar(uint8_t aChar, FILE *stream);
//void lcdSetCursor(uint8_t aString, uint8_t aRow);
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
uint8_t __swap_nibbles(uint8_t aData)
{
	asm volatile("swap %0" : "=r" (aData) : "0" (aData));
	return aData;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
void lcdInitControlLines()
{
	LCD_PORT_DIR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_E);
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
void lcdInitDataLines(LCD_DATA_PORT_DIR direction)
{
	switch (direction)
	{
		case INPUT:
			LCD_PORT_DIR &= ~(1 << LCD_D7)&
							~(1 << LCD_D6)&
							~(1 << LCD_D5)&
							~(1 << LCD_D4);
		break;
		
		case OUTPUT:
			LCD_PORT_DIR |= (1 << LCD_D7)|
							(1 << LCD_D6)|
							(1 << LCD_D5)|
							(1 << LCD_D4);
		break;
	}
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
void lcdToggleEnable(void)
{
	LCD_PORT_STATE &= ~(1 << LCD_E);
	_delay_us(20);
	LCD_PORT_STATE |= (1 << LCD_E);
	_delay_us(20);
	LCD_PORT_STATE &= ~(1 << LCD_E);
	_delay_us(20);
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
void lcdSelectMode(LCD_MODE aMode)
{
	switch (aMode)
	{
		case WRITE:
			LCD_PORT_STATE &= ~(1 << LCD_RW);
		break;
		
		case READ:
			LCD_PORT_STATE |= (1 << LCD_RW);
		break;
	}
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
void lcdSelectRegisters(LCD_REGS aRegType)
{
	switch (aRegType)
	{
		case INSTRUCTION:
			LCD_PORT_STATE &= ~(1 << LCD_RS);
		break;
		
		case DATA:
			LCD_PORT_STATE |= (1 << LCD_RS);
		break;
	}
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
bool lcdIsBusy(void)
{
	uint8_t lcdState = 0;
	uint8_t waitCounter = 100;
	lcdInitDataLines(INPUT);
	lcdSelectMode(READ);
	lcdSelectRegisters(INSTRUCTION);
	do
	{
		LCD_PORT_STATE |= (1 << LCD_E);
		_delay_us(20);
		lcdState = PINB & 0xf0;
		LCD_PORT_STATE &= ~(1 << LCD_E);
		lcdState = __swap_nibbles(lcdState);
		
		LCD_PORT_STATE |= (1 << LCD_E);
		_delay_us(20);
		lcdState |= PINB & 0xf0;
		LCD_PORT_STATE &= ~(1 << LCD_E);
		lcdState = __swap_nibbles(lcdState);
		
	} while(lcdState & (1<<BUSY_FLAG) && (--waitCounter != 0) );
	
	return (!(lcdState & (1<<BUSY_FLAG))) ? true : false;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
void lcdSendData(uint8_t aData)
{
	uint8_t temp = 0;
	
	temp  = LCD_PORT_STATE & 0x0f;
	temp |= (aData & 0xf0);
	LCD_PORT_STATE = temp;
	lcdToggleEnable();
	
	aData = __swap_nibbles(aData);
	temp  = LCD_PORT_STATE & 0x0f;
	temp |= (aData & 0xf0);
	LCD_PORT_STATE = temp;
	lcdToggleEnable();
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
bool lcdWriteCommand(uint8_t aCommand)
{
	if (!lcdIsBusy()) { return false; }
	{
		lcdInitDataLines(OUTPUT);
		lcdSelectMode(WRITE);
		lcdSelectRegisters(INSTRUCTION);
		lcdSendData(aCommand);
	}
	return true;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
bool lcdWriteData(uint8_t aData)
{
	if (!lcdIsBusy()) { return false; }
	{
		lcdInitDataLines(OUTPUT);
		lcdSelectMode(WRITE);
		lcdSelectRegisters(DATA);
		lcdSendData(aData);
	} 
	return true;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
uint8_t lcdInit()
{
	lcdInitControlLines();
	lcdInitDataLines(OUTPUT);
	lcdSelectMode(WRITE);
	lcdSelectRegisters(INSTRUCTION);
	lcdSendData(LCD_FUNCTION_SET(1 << LINE_NUMBER));
		
	if (!lcdWriteCommand(LCD_ON_OFF_CONTROL(DISPLAY) | (CURSOR) | (BLINKING)))
	{
		fprintf(stderr, "FAIL TO WRITE COMMAND 1\r");
		return INIT_FAILED;
	}
	if (!lcdWriteCommand(LCD_CLEAR))
	{
		fprintf(stderr, "FAIL TO WRITE COMMAND 2\r");
		return INIT_FAILED;
	}
	if (!lcdWriteCommand(LCD_ENTRY_MODE_SET(1 << INCREMENT)))
	{
		fprintf(stderr, "FAIL TO WRITE COMMAND 3\r");
		return INIT_FAILED;
	}	
	return INIT_SUCCESS;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
//void lcdPrintChar(uint8_t aChar)
uint16_t lcdPrintChar(uint8_t aChar, FILE *stream)
{
	if (	((aChar >= 'A') && (aChar <= 'Z')) ||
			((aChar >= 'a') && (aChar <= 'z')) ||
			((aChar >= '0') && (aChar <= '9')) ||
			(aChar == ' ') ||
			(aChar == ';') ||
			(aChar == ',') ||
			(aChar == '.') ||
			(aChar == ':')
		)
	{
		if (!lcdWriteData(aChar))
		{
			fprintf(stderr, "WRITE DATA FAILED\r");
		} 
	} 
	else
	{
		fprintf(stderr, "WRONG CHAR\r");
	}
	return 0;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
void lcdSetCursor(uint8_t aString, uint8_t aRow)
{
	//if ( (aString > 1) || (aRow > 16) )
	//{
	//	fprintf(stderr, "CURSOR POSITION IS WRONG\r");
	//} 
	//else
	//{
		switch (aString)
		{
			case 0:
				lcdWriteCommand(LCD_SET_DDRAM(0x00) | aRow);
			break;
			
			case 1:
				lcdWriteCommand(LCD_SET_DDRAM(0x40) | aRow);
			break;
		}
	//}
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
void lcdPrintData(uint8_t aString, uint8_t aRow, uint16_t aData)
{
	uint8_t digit1 = 0;
	uint8_t digit2 = 0;
	uint8_t digit3 = 0;
	uint8_t digit4 = 0;
	
	digit1 = (aData * 0.0001);
	if (digit1 == 0)
	{
		digit1 = ' ';
	}
	else
	{
		digit1 += '0';
	}
	lcdSetCursor(aString, aRow);
	fprintf(stdout, "%c", digit1);
	
	digit2 = (aData * 0.001);
	digit2 %= 10;
	digit2 += '0';
	fprintf(stdout, "%c", digit2);
	
	digit3 = (aData * 0.01);
	digit3 %= 10;
	digit3 += '0';
	lcdSetCursor(aString, aRow + 3);
	fprintf(stdout, "%c", digit3);

	digit4 = (aData * 0.1);
	digit4 %= 10;
	digit4 += '0';
	fprintf(stdout, "%c", digit4);
}