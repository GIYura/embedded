#ifndef PCF8583_H_
#define PCF8583_H_

#include "../definitions/defs.h"

#define PCF_ADDR		0xa0
#define PCF_SEC_REG		0x02

void pcfConvertRawData(T_PCF_RAW_DATA *pcfData);
void convertASCII_2_BCD(char *buff, T_PCF_WR_DATA *pcfSt);

#endif /* PCF8583_H_ */