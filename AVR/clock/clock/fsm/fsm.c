#include "fsm.h"

uint8_t (*f[])(uint8_t*) = {	 
								fsmStartCond, 
								fsmSendB, 
								fsmReceiveB, 
								fsmReceiveLB, 
								fsmStopCond
							};
							
uint8_t iterationNumber = 0;
	
T_FSM_STATE currentState;

T_INIT fsmInit(void)
{
	fsmSetCurrentState(IIC_START);
	return INIT_SUCCESS;
}

void fsmSetCurrentState(T_FSM_STATE nState)
{
	if (nState < ICC_N_STATE)
	{
		currentState = nState;
	}
}

T_FSM_STATE fsmGetCurrentState(void)
{
	return currentState;
}

uint8_t fsmRun(void)
{
	uint8_t res = 0;
	if (fsmGetCurrentState() < ICC_N_STATE)
	{
		res = (*f[fsmGetCurrentState()])(&iterationNumber);
	}
	return res;
}

void fsmProcess(uint8_t aRes, T_PCF_RAW_DATA *pcfData)
{
	T_FSM_STATE sts = 0;
	sts = fsmGetCurrentState();
	switch(sts)
	{
		case IIC_START:
			
				switch (iterationNumber)
				{
					case 0:
							if ( (aRes & TW_NO_INFO) == TW_START )
							{
								fsmSetCurrentState(IIC_SEND);
#ifdef DEBUG_INFO
								printf("START SUCCESS\n");
#endif
							}
							else
							{
#ifdef DEBUG_INFO
								printf("ERROR: START FAILED\n");
#endif
							}	
					break;
					
					case 1: 
							if ( (aRes & TW_NO_INFO) == TW_REP_START )
							{
								fsmSetCurrentState(IIC_SEND);
#ifdef DEBUG_INFO
								printf("REP. START SUCCESS\n");
#endif
							}
							else
							{
#ifdef DEBUG_INFO
								printf("ERROR: REP. START FAILED\n");
#endif
							}
					break;
					
					default: break;
				}
#ifdef DEBUG_INFO
				printf("CASE START. ITERATION: %d\n", iterationNumber);
				printf("FSM STATE: %d\n", fsmGetCurrentState());
				printf("PREV. OPER. RES.:%xh\n", aRes);
				printf("------------------------------------\n");
#endif
		break;
		
		case IIC_SEND:
		
				switch (iterationNumber)
				{
					case 0:
							if ( (aRes & TW_NO_INFO) == TW_MT_SLA_ACK )
							{
#ifdef DEBUG_INFO
								printf("CASE 0. SEND: SLA + W; RECEIVE: ACK\n");
#endif
							}
							else if ((aRes & TW_NO_INFO) == TW_MT_SLA_NACK)
							{
#ifdef DEBUG_INFO
								printf("CASE 0. SEND: SLA + W; RECEIVE: NACK\n");
#endif
							}
							else
							{
#ifdef DEBUG_INFO
								printf("CASE 0. ERROR: SEND SLA + W FAILED\n");
#endif
							}
#ifdef DEBUG_INFO
							printf("CASE 0. ITERATION: %d\n", iterationNumber);
							printf("FSM STATE: %d\n", fsmGetCurrentState());
							printf("PREV. OPER. RES.:%xh\n", aRes);
							printf("------------------------------------\n");
#endif
					break;
				
					case 1:
							if ( (aRes & TW_NO_INFO) == TW_MT_DATA_ACK )
							{
#ifdef DEBUG_INFO
								printf("CASE 1. SEND: DATA BYTE; RECEIVE: ACK\n");
#endif
								fsmSetCurrentState(IIC_START);
							}
							else if ((aRes & TW_NO_INFO) == TW_MT_DATA_NACK)
							{
#ifdef DEBUG_INFO
								printf("CASE 1. SEND: DATA BYTE; RECEIVE: NACK\n");
#endif
							}
							else
							{
#ifdef DEBUG_INFO
								printf("CASE 1. ERROR: SEND DATA BYTE FAILED\n");
#endif
							}
#ifdef DEBUG_INFO
							printf("CASE 1. ITERATION: %d\n", iterationNumber);
							printf("FSM STATE: %d\n", fsmGetCurrentState());
							printf("PREV. OPER. RES.:%xh\n", aRes);
							printf("------------------------------------\n");
#endif
					break;
				
					case 2:
							if ( (aRes & TW_NO_INFO) == TW_MR_SLA_ACK )
							{
#ifdef DEBUG_INFO
								printf("CASE 2. SEND: SLA + R; RECEIVE: ACK\n");
#endif
								fsmSetCurrentState(IIC_RECEIVE);
							}
							else if ((aRes & TW_NO_INFO) == TW_MR_SLA_NACK)
							{
#ifdef DEBUG_INFO
								printf("CASE 2. SEND: SLA + R; RECEIVE: NACK\n");
#endif
							}
							else
							{
#ifdef DEBUG_INFO
								printf("CASE 2. ERROR: RECEIVE FAILED\n");
#endif
							}
#ifdef DEBUG_INFO
							printf("CASE 2. ITERATION: %d\n", iterationNumber);
							printf("FSM STATE: %d\n", fsmGetCurrentState());
							printf("PREV. OPER. RES.:%xh\n", aRes);
							printf("------------------------------------\n");
#endif
					break;
				}
		break;
		
		case IIC_RECEIVE:
				if (iterationNumber == 0)
				{
					pcfData->sec = aRes;
				} 
				else
				{
					pcfData->min = aRes;
					fsmSetCurrentState(IIC_RECEIVE_LAST);
				}
#ifdef DEBUG_INFO
				printf("CASE RECEIVE. ITERATION: %d\n", iterationNumber);
				printf("FSM STATE: %d\n", fsmGetCurrentState());
				printf("PREV. OPER. RES.:%xh\n", aRes);
				printf("------------------------------------\n");
#endif
		break;
		
		case IIC_RECEIVE_LAST:
				pcfData->hour = aRes;
				fsmSetCurrentState(IIC_STOP);
#ifdef DEBUG_INFO
				printf("CASE RECEIVE LAST BYTE. ITERATION: %d\n", iterationNumber);
				printf("FSM STATE: %d\n", fsmGetCurrentState());
				printf("PREV. OPER. RES.:%xh\n", aRes);
				printf("------------------------------------\n");
#endif
		break;
		
		case IIC_STOP:
			fsmSetCurrentState(IIC_START);
#ifdef DEBUG_INFO
			printf("CASE STOP. ITERATION: %d\n", iterationNumber);
			printf("FSM STATE: %d\n", fsmGetCurrentState());
			printf("PREV. OPER. RES.:%xh\n", aRes);
			printf("+++++++++++++++++++++++++++++++++++\n");
			printf("+++++++++++++++++++++++++++++++++++\n");
			printf("+++++++++++++++++++++++++++++++++++\n");
#endif
		break;
		
		default: break;
	}
}