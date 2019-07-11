#include "Esp.h"
#include "Uart.h"

#include <stdint.h>
#include <stdio.h>

static Driver::Uart* uart = new Driver::Uart();
static Module::Esp* esp = new Module::Esp();

//constructor
Module::Esp::Esp(){

}

//destructor
Module::Esp::~Esp(){

}

//init esp
Module::Esp::esp_init_state_t Module::Esp::init(void){

    if(NULL == uart){
	printf("Esp.cpp. Can't create UART instance\n");
	return ESP_ERROR;
    }
    if(NULL == esp){
	printf("Esp.cpp. Can't create ESP instance\n");
        return ESP_ERROR;
    }

//uart init
    uart->init(Driver::Uart::UART_1, Driver::Uart::S_115200);

    esp->setEspState(ESP_SEND_CMD);

    esp->sendCommand(esp->getAtCommand(AT));
    esp->sendCommand(esp->getAtCommand(AT_RESTORE));
    esp->sendCommand(esp->getAtCommand(AT_GMR));
    esp->sendCommand(esp->getAtCommand(AT_UART_CUR));
    esp->sendCommand(esp->getAtCommand(AT_GMR));
    esp->sendCommand(esp->getAtCommand(AT_GSLP));

}