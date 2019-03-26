#ifndef FSM_H_
#define FSM_H_

#include "../definitions/defs.h"
#include "../i2c/i2c.h"
#include "fsmCfg.h"

typedef enum
{
	IIC_START = 0,
	IIC_SEND,
	IIC_RECEIVE,
	IIC_RECEIVE_LAST,
	IIC_STOP,
	ICC_N_STATE
} T_FSM_STATE;

T_INIT fsmInit(void);
uint8_t fsmRun(void);
void fsmProcess(uint8_t aIICState, T_PCF_RAW_DATA *pcfData);

void fsmSetCurrentState(T_FSM_STATE nState);
T_FSM_STATE fsmGetCurrentState(void);

#endif /* FSM_H_ */