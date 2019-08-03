#ifndef _AT_PARSER_H
#define _AT_PARSER_H

#include <stdint.h>

namespace Parser{
    class At_parser{

	enum at_buff_t{
	    AT_BUFF_SHORT    = 64,
	    AT_BUFF_MIDDLE   = 512,
	    AT_BUFF_LONG     = 1024
        };
	
	enum at_status_t{
	    AT_STATUS_OK     = 0,
	    AT_STATUS_ERROR,
	    AT_STATUS_BUSY
        };
	
	enum at_state_t{
	    AT_INIT          = 0,
	    AT_UNINIT
        };

	enum at_init_cmd_t{
	    AT_RST	     = 0,
	    AT,
	    AT_VER,
	    AT_INIT_NUM
	};

        enum at_conn_cmd_t{
	    AT_MODE	    = 0,
	    AT_AP_CONN,
	    AT_AP_DISCONN,
	    AT_STATUS,
	    AT_SEND,
	    AT_START,
	    AT_CONN_NUM
	};

	typedef struct{
	    const char* cmd;
	    const char* param;
	    const char* resp_start;
	    const char* resp_end;
	}command_t;

	command_t at_init_cmd[AT_INIT_NUM] =  {
						  {   "+RST",	      "",     "AT+RST",		"ready"   },
						  {   "",	      "",     "AT",		"OK"      },
						  {   "+GMR",	      "",     "AT",		"OK"      }
					      };

	command_t at_conn_cmd[AT_CONN_NUM] =  {
						  {   "+CWMODE=",     "1",    "AT+CWMODE",	"OK"	  },
						  {   "+CWJAP?",      "",     "AT+CWJAP",	"OK"	  },
						  {   "+CWQAP",	      "",     "AT+CWQAP",	"OK"	  },
						  {   "+CIPSTATUS",   "",     "STATUS:",	"OK"	  },
						  {   "+CIPSEND",     "",     "SEND",		"OK"	  },
						  {   "+CIPSTART",    "",     "AT+CIPSTART",	"OK"	   }
					      };

	char cmd_buff[AT_BUFF_MIDDLE] = { 0 };
	char resp_buff[AT_BUFF_MIDDLE] = { 0 };
        at_state_t init_state;
	uint16_t parsingTime;

	at_status_t fetch_string(char* resp_buff, uint16_t* rec_len, uint16_t max_len, const char* search_str, uint32_t timeout);
        at_status_t setTimeout(uint16_t timeout);
        bool getTimeout(void);


	public:
	    At_parser();
	    ~At_parser();
	
	    at_status_t send_cmd(const char* cmd, const char* param);
	    at_status_t receive_resp(const char* resp_start, const char* resp_end, char** res_data, uint32_t timeout);

    };
}

#endif