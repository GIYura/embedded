#ifndef ADC_H_
#define ADC_H_

#include "../definitions/defs.h"

uint8_t adcInit(uint8_t aVref, TadcCoeff *aAdcCoeff);
uint16_t* getVoltageCode(void);
uint16_t* getCurrentCode(void);
double adcCodeProcess(uint16_t *iPtr);

#endif /* ADC_H_ */