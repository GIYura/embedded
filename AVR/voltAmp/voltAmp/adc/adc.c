#include "adc.h" 

#define VOLTAGE			0
#define CURRENT			1

#define R1				12.7
#define R2				2.2
#define R3				1.1
#define R4				4.9
#define R5				1
#define R6				5.1
#define MEASURE_NUMBER	10

typedef struct
{
	uint16_t voltageCode[MEASURE_NUMBER];
	uint16_t currentCode[MEASURE_NUMBER];
	uint8_t channel;
	uint8_t voltageCodeIdx;
	uint8_t currentCodeIdx;
} TadcData;
#define  T_ADC_DATA_SZ sizeof(TadcData)
static TadcData adcData = {{0}, {0}, VOLTAGE, 0, 0};
//-----	------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
uint8_t adcInit(uint8_t aVref, TadcCoeff *aAdcCoeff)
{
	switch (aVref)
	{
		case VREF_2_5:
			ADMUX |= (1 << REFS1) | (1 << REFS0);
			aAdcCoeff->vRef = (double)2.56;
		break;
		
		case VREF_5_0:
			ADMUX |= (1 << REFS0);
			aAdcCoeff->vRef = (double)5.00;
		break;
	}
	ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADPS2);
	ADCSRA |= (1 << ADSC);
	aAdcCoeff->resolution = pow(2, 10);
	aAdcCoeff->rDividerCoeffV = ((double)R1 + (double)R2) / (double)R2;
	aAdcCoeff->rDividerCoeffA = ((double)R3 + (double)R4) / (double)R4;
	aAdcCoeff->amplifierCoeff = ((double)1 + (double)R6 / (double)R5) * 0.1;
	return INIT_SUCCESS;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
ISR(ADC_vect)
{
	cli();
	uint8_t sreg = SREG;
	switch (adcData.channel)
	{
		case VOLTAGE:
			adcData.voltageCode[adcData.voltageCodeIdx++] = ADCW;
			if (adcData.voltageCodeIdx == MEASURE_NUMBER)
			{
				adcData.voltageCodeIdx = 0;
			}
			//adcData.channel = CURRENT;
			//ADMUX |= (1 << MUX0);
		break;
		
		case CURRENT:
			adcData.currentCode[adcData.currentCodeIdx++] = ADCW;
			if (adcData.currentCodeIdx == MEASURE_NUMBER)
			{
				adcData.currentCodeIdx = 0;
			}
			adcData.channel = VOLTAGE;
			ADMUX &= ~(1 << MUX0);
		break;
	}
	ADCSRA |= (1 << ADSC);
	SREG = sreg;
	sei();
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
uint16_t* getVoltageCode(void)
{
	return adcData.voltageCode;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
uint16_t* getCurrentCode(void)
{
	return adcData.currentCode;
}
//-----------------------------------------------------------------------------------------//
//
//-----------------------------------------------------------------------------------------//
double adcCodeProcess(uint16_t *iPtr)
{
	uint16_t sum = 0;
	double res = 0.0;
	uint16_t tempArr[MEASURE_NUMBER] = {0};
	
	memcpy((void*)&tempArr, iPtr, sizeof(tempArr));
	
/*	for (uint8_t i = 0; i < MEASURE_NUMBER; i++)
	{
		fprintf(stderr, "Code ADC[%d] = %x\r", i, tempArr[i]);
	}
	*/
	//return res;
		
	for (uint8_t i = 1; i < MEASURE_NUMBER; i++)
	{
		for (uint8_t j = 0; j < MEASURE_NUMBER - 1; j++)
		{
			if (tempArr[j] < tempArr[j + 1])
			{
				uint16_t temp = tempArr[j];
				tempArr[j] = tempArr[j + 1];
				tempArr[j + 1] = temp;
			}
		}
	}
	tempArr[0] = 0;
	tempArr[MEASURE_NUMBER - 1] = 0;
	
	for (uint8_t i = 0; i < MEASURE_NUMBER; i++)
	{
		sum += tempArr[i];
	}
	return res = sum / (double)8;	
}
