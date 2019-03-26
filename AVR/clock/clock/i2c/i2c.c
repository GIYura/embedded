#include "i2c.h"

uint8_t i2cInit(void)
{
//	SCL frequency = CPU Clock frequency / (16 + 2 * TWBR *4 pow (TWPS)
	return INIT_SUCCESS;
}
/*
uint8_t i2cStartCondition(uint8_t dummy)
{
	dummy = 0;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
//цикл ожидания будет вполняться дол тех пор, пока заданный разряд переменной содержит 0.
	loop_until_bit_is_set(TWCR, TWINT);
	return TWSR;
}

uint8_t i2cSendByte(uint8_t aByte)
{
	TWDR = aByte;
	TWCR = (1 << TWINT) | (1 << TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
	return TWSR;	
}

uint8_t i2cReceiveByte(uint8_t dummy)
{
	TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
	loop_until_bit_is_set(TWCR, TWINT);
	return TWDR;
}

uint8_t i2cReceiveLastByte(uint8_t dummy)
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
	return TWDR;
}

uint8_t i2cStopCondition(uint8_t dummy)
{
	TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
	loop_until_bit_is_clear(TWCR, TWSTO);
	return 0;
}
*/
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
uint8_t fsmStartCond(uint8_t *pN)
{
	static uint8_t counter = 0;
	*pN = counter;	
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
	if (++counter > 1)
	{
		counter = 0;
	}
	return TWSR;
}

uint8_t fsmSendB(uint8_t *pN)
{
	static uint8_t counter = 0;
	uint8_t aByte = 0;
	
	switch (counter)
	{
		case 0:
				aByte = (I2C_CMD(PCF_ADDR) | TW_WRITE);
				*pN = counter;
				counter++;
		break;
		
		case 1:
				aByte = PCF_SEC_REG;
				*pN = counter;
				counter++;
		break;
		
		case 2:
				aByte = (I2C_CMD(PCF_ADDR) | TW_READ);
				*pN = counter;
				counter = 0;
		break;
		
		default: break;
	}
	TWDR = aByte;
	TWCR = (1 << TWINT) | (1 << TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
	return TWSR;
}

uint8_t fsmReceiveB(uint8_t *pN)
{
	static uint8_t counter = 0;
	
	*pN = counter;
	if (++counter > 1)
	{
		counter = 0;
	}
	
	TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT);
	loop_until_bit_is_set(TWCR, TWINT);
	return TWDR;
}

uint8_t fsmReceiveLB(uint8_t *pN)
{
	//fsmSetCurrentState(IIC_STOP);
	//printf("Receive last byte: %d\n", fsmGetCurrentState());
	static uint8_t counter = 0;
	*pN = counter;
	TWCR = (1 << TWINT) | (1 << TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
	return TWDR;
}

uint8_t fsmStopCond(uint8_t *pN)
{
	//fsmSetCurrentState(IIC_START);
	//printf("Stop: %d\n", fsmGetCurrentState());	
	//printf("------------------------------\n");
	static uint8_t counter = 0;
	*pN = counter;
	TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
	loop_until_bit_is_clear(TWCR, TWSTO);
	return 0;
}