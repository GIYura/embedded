#ifndef I2C_H_
#define I2C_H_

#include "../definitions/defs.h"
#include "../pcf8583/pcf8583.h"
#include "util/twi.h"

uint8_t i2cInit(void);
uint8_t fsmStartCond(uint8_t *pN);
uint8_t fsmSendB(uint8_t *pN);
uint8_t fsmReceiveB(uint8_t *pN);
uint8_t fsmReceiveLB(uint8_t *pN);
uint8_t fsmStopCond(uint8_t *pN);

#endif /* I2C_H_ */