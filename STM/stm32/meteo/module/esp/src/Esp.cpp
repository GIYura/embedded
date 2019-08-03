#include "Esp.h"
#include "Uart.h"
#include "Fifo.h"
#include "Ring.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern Buffer::Ring *ring;
extern Buffer::Fifo *fifo;

static Driver::Uart* uart = new Driver::Uart();
static Module::Esp* esp = new Module::Esp();

//constructor
Module::Esp::Esp(){
    setEspStage(ESP_SEND_CMD);
    setEspState(ESP_UNINIT);

    setAtCommand(AT);
    setAtResponce(AT_OK);

    initAttemptNumber = 3;
}

//destructor
Module::Esp::~Esp(){

}

//init esp
Module::Esp::esp_state_t Module::Esp::init(void){

    if(NULL == uart){
	printf("Esp.cpp. Can't create UART instance\n");
	return ESP_ERROR;
    }
    if(NULL == esp){
	printf("Esp.cpp. Can't create ESP instance\n");
        return ESP_ERROR;
    }

//uart init
    if(uart->init(Driver::Uart::UART_1, Driver::Uart::S_115200) == Driver::Uart::UART_FAILED){
	printf("Error. Can't init UART\n");
    }

    while(getEspState() != ESP_INIT){
	switch(getEspStage()){
	    case ESP_SEND_CMD: {
		switch(getAtCommand()){
		    case AT:
			sendCommand(getAtCommand(AT));
			setAtResponce(AT_OK);
			setEspStage(ESP_RECEIVE_RESPONCE);
		    break;

		    case AT_RST:
			sendCommand(getAtCommand(AT_RST));
			setAtResponce(AT_OK_READY);
			setEspStage(ESP_RECEIVE_RESPONCE);
		    break;

		    case AT_RESTORE:
			sendCommand(getAtCommand(AT_RESTORE));
			setAtResponce(AT_OK);
			setEspStage(ESP_RECEIVE_RESPONCE);
		    break;
		}
	    }
	    break;


	    case ESP_RECEIVE_RESPONCE: {
		receiveResponce(rxBuff, &responceLen);

		switch(getAtResponce()){
		    case AT_OK:
			if(strncmp(rxBuff, getAtResponce(AT_OK), strlen(getAtResponce(AT_OK))) == 0){
			    printf("");
			    setAtCommand(AT_RST);
			    setEspStage(ESP_SEND_CMD);
			} else {
			    printf("");
			}
		    break;
  
		    case AT_OK_READY:
			if(strncmp(rxBuff, getAtResponce(AT_OK_READY), strlen(getAtResponce(AT_OK_READY))) == 0){
			    printf("");
			    setAtCommand(AT_RESTORE);
			    setEspStage(ESP_SEND_CMD);
			} else {
			    printf("");
			}
		    break;
		}
	    }
	    break;

	    default : break;
	}
    }


    return ESP_SUCCESS;
}

//
Module::Esp::esp_state_t Module::Esp::sendCommand(const char* cmd){
    uint16_t len = strlen(cmd);
    if(NULL == len){
	printf("Error. Wrong command\n");
	return ESP_ERROR;
    }
    uint8_t data;

    for(uint8_t i = 0; i < len; ++i){
	data = *cmd++;
	fifo->push(data);
    }
    fifo->pop(&data);
//    uart->sendData(data);
    return ESP_SUCCESS;
}

//
Module::Esp::esp_state_t Module::Esp::receiveResponce(char* resp, uint16_t* len){
    if(NULL == resp){
	printf("Error. Wrong responce address\n");
	return ESP_ERROR;
    }

    while(ring->pop((uint8_t*)resp)){
	(*len)++;
	resp++;
    }
    return ESP_SUCCESS;
}

//
void Module::Esp::setEspState(Module::Esp::esp_state_t newState){
    switch(newState){
	case ESP_INIT:
	    espState = ESP_INIT;
	break;

	case ESP_UNINIT:
	    espState = ESP_UNINIT;
	break;

	case ESP_ERROR:
	    espState = ESP_ERROR;
	break;

	case ESP_SUCCESS:
	    espState = ESP_SUCCESS;
	break;

	default : break;
    }
}

//
void Module::Esp::setEspStage(Module::Esp::esp_stage_t newState){
    switch(newState){
	case ESP_SEND_CMD:
	    espStage = ESP_SEND_CMD;
	break;

	case ESP_RECEIVE_RESPONCE:
	    espStage = ESP_RECEIVE_RESPONCE;
	break;

	default : break;
    }
}

void Module::Esp::setAtResponce(at_responce_t atResponce){
    if( (atResponce < AT_OK) || (atResponce >= AT_RES_NUMBER) ){
	return;
    }
    at_responce = atResponce;
}

Module::Esp::at_responce_t Module::Esp::getAtResponce(void){
    return at_responce;
}

void Module::Esp::setAtCommand(at_command_t atCommand){
    if( (atCommand < AT) || (atCommand >= AT_CMD_NUMBER) ){
	return;
    }
    at_command = atCommand;
}

Module::Esp::at_command_t Module::Esp::getAtCommand(void){
    return at_command;
}