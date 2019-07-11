#ifndef _ESP_H
#define _ESP_H

namespace Module{
    class Esp{
	

	  private:
		enum esp_work_state_t{
		    ESP_SEND_CMD,
		    ESP_RECEIVE_RESPONCE
		};

		enum esp_init_state_t{
		    ESP_SUCCESS = 0,
		    ESP_ERROR
		};

		enum at_command_t{
		    AT,				  //test AT startup
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
		const char* atResponce[AT_RES_NUMBER]	= {   "OK",
							      
							  };

		esp_work_state_t espState;
		const char* getAtCommand(at_command_t);
		void setEspState(esp_work_state_t);
                esp_work_state_t getEspState(void);
	public:
	    
	    Esp();
	    virtual ~Esp();
	    esp_init_state_t init(void);
	    esp_init_state_t sendCommand(const char*);
	    esp_init_state_t receiveResponce(char*);
    };
}

#endif