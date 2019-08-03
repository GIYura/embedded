#include "At_parser.h"
#include "Uart.h"

#include <stdio.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static Driver::Uart* uart = new Driver::Uart();

Parser::At_parser::At_parser(){
    if(nullptr == uart){
#ifdef DEBUG_INFO
printf("Can't create UART instnce\n");
#endif
    }
}

Parser::At_parser::~At_parser(){

}

Parser::At_parser::at_status_t Parser::At_parser::send_cmd(const char* cmd, const char* param){
    if(nullptr == cmd){
	return AT_STATUS_ERROR;
#ifdef DEBUG_INFO
printf("Incorrect AT command\n");
#endif
	return AT_STATUS_ERROR;
    }

    sprintf(cmd_buff, "AT");
    
    strcat(cmd_buff, cmd);

    if(nullptr != param){
	strcat(cmd_buff, param);
    }

    strcat(cmd_buff, "\r\n");
    
    uart->sendData((uint8_t*)cmd_buff, strlen(cmd_buff));

    return AT_STATUS_OK;
}


Parser::At_parser::at_status_t Parser::At_parser::receive_resp(const char* resp_start, const char* resp_end, char** resp_data, uint32_t timeout){
    if(init_state != AT_INIT){
        return AT_STATUS_ERROR;
    }
    *resp_data = NULL;
    //uint32_t current_time = TimerSysMs_getTicks();
    uint16_t start_len = 0;

    memset(resp_buff, 0, sizeof(resp_buff));
    uint16_t rec_len = 0;
    
    if(resp_start != NULL){
        start_len = strlen(resp_start);
            if(AT_STATUS_OK != fetch_string(resp_buff, &rec_len, AT_BUFF_MIDDLE, resp_start, timeout)){
            return AT_STATUS_ERROR;
        }
//if there are some bytes in front of what we needed
        if(rec_len > start_len){
            memcpy(&resp_buff[0], &resp_buff[rec_len - start_len], start_len);
        }
    }

    memset(&resp_buff[start_len], 0, sizeof((resp_buff) - start_len));

    if(resp_end != NULL){
        if(AT_STATUS_OK != fetch_string(&resp_buff[start_len], &rec_len, AT_BUFF_MIDDLE - start_len, resp_end, timeout)){
            return AT_STATUS_ERROR;
        }
    } else {
        rec_len = 0;
    }
    
    resp_buff[MIN(rec_len + start_len, AT_BUFF_MIDDLE - 1)] = '\0';

    if(resp_data != NULL){
        *resp_data = (char*)&resp_buff[start_len];
    }
    return AT_STATUS_OK;
}

//
Parser::At_parser::at_status_t Parser::At_parser::fetch_string(char* resp_buff, uint16_t* rec_len, uint16_t max_len, const char* search_str, uint32_t timeout){
    if(search_str == NULL || init_state == AT_UNINIT){
        return AT_STATUS_ERROR;
    }

    //setTimeout(timeout);
    *rec_len = 0;

    uint16_t l_search_str_len = strlen(search_str);
    uint16_t idx = 0;
    uint16_t len = 0;
  
    do {              //while until search str, timeout, buff is FULL
        len = 0;
        if(uart->receiveData((uint8_t*)resp_buff, &len)){
            (*rec_len)++;
            if(*resp_buff == search_str[idx]){
                idx++;
                    if(idx == l_search_str_len){
                    return AT_STATUS_OK;
                }
            } else {
                idx = 0;
            }
            resp_buff++;
            max_len--;
            if(max_len == 0){
                break;
            }
        }
    } while(!getTimeout());

    return AT_STATUS_ERROR;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------
/*
@brief: Function to set timeout.
@details
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------------
Parser::At_parser::at_status_t Parser::At_parser::setTimeout(uint16_t time) {
    //parsingTime = (uint16_t)TimerSysMsPort_getTicks() + time;
    return AT_STATUS_OK;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
/*
@brief: Function to get timeout.
@details
*/
//-----------------------------------------------------------------------------------------------------------------------------------------------------
bool Parser::At_parser::getTimeout(void) {
    //if((uint16_t)(TimerSysMsPort_getTicks() - m_parsingTime + 0xFF00) >= 0xFF00){     
//        return true;
//    } else {
//        return false;
//    }
}






