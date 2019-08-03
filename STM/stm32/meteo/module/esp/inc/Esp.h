#ifndef _ESP_H
#define _ESP_H

#include <stdint.h>

namespace Module{
    class Esp{
	
	  private:
		enum esp_stage_t{
		    ESP_SEND_CMD = 0,
		    ESP_RECEIVE_RESPONCE
		};

		enum esp_state_t{
		    ESP_SUCCESS = 0,
		    ESP_UNINIT,
		    ESP_INIT,
		    ESP_ERROR,
		};

		enum at_command_t{
		    AT = 0,			  //test AT startup
		    AT_RST,			  //restart
		    AT_GMR,			  //check version info
		    AT_GSLP,			  //enter deep sleep mode
		    AT_E,			  //echo
		    AT_RESTORE,			  //restore default settings
		    AT_UART_CUR,		  //current configuration
		    AT_CMD_NUMBER
		};

		enum at_responce_t{
		    AT_OK,
		    AT_OK_READY,
		    AT_RES_NUMBER
		};

		const char* atCommand[AT_CMD_NUMBER]    = {   "AT\r\n",
							      "AT+RST\r\n",
							      "AT+GMR\r\n",
							      "AT+GSLP\r\n",
							      "ATE\r\n",
							      "AT+RESTORE\r\n",
							      "AT+UART_CUR?\n\r"
							  };

		const char* atResponce[AT_RES_NUMBER]	= {   "\r\nOK\r\n",
							      "\r\nOK\r\nready\r\n"
							  };

		char rxBuff[2048];		  //buffer to receive responce
		uint16_t responceLen;

		esp_stage_t espStage;		  //current stage
		esp_state_t espState;		  //current state

                at_command_t at_command;	  //current AT command number
		at_responce_t at_responce;	  //current AT responce number
		
		uint8_t initAttemptNumber;

		const char* getAtCommand(at_command_t);
		const char* getAtResponce(at_responce_t);

		void setEspState(esp_state_t);
                esp_state_t getEspState(void);

                void setEspStage(esp_stage_t);
                esp_stage_t getEspStage(void);

		void setAtResponce(at_responce_t);
		at_responce_t getAtResponce(void);

                void setAtCommand(at_command_t);
		at_command_t getAtCommand(void);
		
	public:
	    
	    Esp();
	    virtual ~Esp();
	    esp_state_t init(void);
	    esp_state_t sendCommand(const char*);
	    esp_state_t receiveResponce(char*, uint16_t*);

    };
}

#endif