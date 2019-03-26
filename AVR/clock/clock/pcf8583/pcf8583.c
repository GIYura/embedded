#include "pcf8583.h"

/*
*
*/
void pcfConvertRawData(T_PCF_RAW_DATA *pcfData)
{
	static uint8_t sec_prev = 0;
	uint8_t secBCD = pcfData->sec;
	uint8_t secBCDCopy = secBCD;
	uint8_t sec_current = secBCD;
	
	uint8_t minBCD = pcfData->min;
	uint8_t minBCDCopy = minBCD;
	
	uint8_t hourBCD = pcfData->hour;
	uint8_t hourBCDCopy = hourBCD;
	
	if (pcfData->ready == 0)
	{
//convert BCD 2 ASCII
		secBCD &= 0x0f;
		secBCD += '0';
		secBCDCopy &= 0xf0;
		secBCDCopy >>= 4;
		secBCDCopy += '0';
		
		minBCD &= 0x0f;
		minBCD += '0';
		minBCDCopy &= 0xf0;
		minBCDCopy >>= 4;
		minBCDCopy += '0';
		
		hourBCD &= 0x0f;
		hourBCD += '0';
		hourBCDCopy &= 0xf0;
		hourBCDCopy >>= 4;
		hourBCDCopy += '0';
				
		printf("%s%c%c%c%c%c%c%c%c\r", "Current time: ",
		hourBCDCopy, hourBCD, ':', 
		minBCDCopy, minBCD, ':', 
		secBCDCopy, secBCD);
		
		pcfData->ready = 1;
	}
	
	if (sec_current != sec_prev)				//check 2 consecutive values of sec
	{
		sec_prev = sec_current;					//update previous value
		pcfData->ready = 0;
	}
}

void convertASCII_2_BCD(char *buff, T_PCF_WR_DATA *pcfSt)
{
	pcfSt->sec = ((buff[7] - 0x30) << 4) + (buff[6] - 0x30);
	pcfSt->min = ((buff[4] - 0x30) << 4) + (buff[3] - 0x30);
	pcfSt->hour = ((buff[1] - 0x30) << 4) + (buff[0] - 0x30);
}