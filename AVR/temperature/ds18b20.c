#include "ds18b20.h"

uint8_t ds18b20_reset()
{
	uint8_t i;

	//low for 480us
	THERM_LOW;
	THERM_OUTPUT_MODE;
	_delay_us(480);

	//release line and wait for 60uS
	THERM_INPUT_MODE;
	_delay_us(60);

	//get value and wait 420us
	i = (DS18B20_PIN & (1<<DS18B20_DQ));
	_delay_us(420);

	//return the read value, 0=ok, 1=error
	return i;
}

/*
 * write one bit
 */
void ds18b20_writebit(uint8_t bit)
{
	//low for 1uS
//	DS18B20_PORT &= ~ (1<<DS18B20_DQ); //low
//	DS18B20_DDR |= (1<<DS18B20_DQ); //output
	THERM_LOW;
	THERM_OUTPUT_MODE;
	_delay_us(1);

	//if we want to write 1, release the line (if not will keep low)
	if(bit)
//		DS18B20_DDR &= ~(1<<DS18B20_DQ); //input
		THERM_INPUT_MODE;

	//wait 60uS and release the line
	_delay_us(60);
//	DS18B20_DDR &= ~(1<<DS18B20_DQ); //input
	THERM_INPUT_MODE;
}

/*
 * read one bit
 */
uint8_t ds18b20_readbit(void)
{
	uint8_t bit = 0;

	//low for 1uS
//	DS18B20_PORT &= ~ (1<<DS18B20_DQ); //low
//	DS18B20_DDR |= (1<<DS18B20_DQ); //output
	THERM_LOW;
	THERM_OUTPUT_MODE;
	_delay_us(1);

	//release line and wait for 14uS
//	DS18B20_DDR &= ~(1<<DS18B20_DQ); //input
	THERM_INPUT_MODE;
	_delay_us(14);

	//read the value
	if(DS18B20_PIN & (1<<DS18B20_DQ))
		bit = 1;

	//wait 45uS and return read value
	_delay_us(45);
	return bit;
}

/*
 * write one byte
 */
void ds18b20_writebyte(uint8_t byte)
{
	uint8_t i = 8;
	while(i--)
	{
		ds18b20_writebit(byte&1);
		byte >>= 1;
	}
}

/*
 * read one byte
 */
uint8_t ds18b20_readbyte(void)
{
	uint8_t i = 8, n = 0;
	while(i--)
	{
		n >>= 1;
		n |= (ds18b20_readbit()<<7);
	}
	return n;
}

/*
 * get temperature
 */
double ds18b20_gettemp()
{
	uint8_t temperature_l;
	uint8_t temperature_h;
	double retd = 0;

	#if DS18B20_STOPINTERRUPTONREAD == 1
	cli();
	#endif

	if (ds18b20_reset())
	{
		printf("%s\r", "Sensor is not connected");
		return retd = 0;
	}
	else
	{
		ds18b20_writebyte(DS18B20_CMD_SKIPROM); //skip ROM
		ds18b20_writebyte(DS18B20_CMD_CONVERTTEMP); //start temperature conversion

		while(!ds18b20_readbit()); //wait until conversion is complete

		ds18b20_reset(); //reset
		ds18b20_writebyte(DS18B20_CMD_SKIPROM); //skip ROM
		ds18b20_writebyte(DS18B20_CMD_RSCRATCHPAD); //read scratchpad

//read 2 byte from scratchpad
		temperature_l = ds18b20_readbyte();
		temperature_h = ds18b20_readbyte();

		#if DS18B20_STOPINTERRUPTONREAD == 1
		sei();
		#endif

		//convert the 12 bit value obtained
		retd = ((temperature_h << 8 ) + temperature_l) * 0.0625;
	}
	return retd;
}

