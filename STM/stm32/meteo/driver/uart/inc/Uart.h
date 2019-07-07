#ifndef _UART_H
#define _UART_H

#include <stdint.h>

namespace Driver{
    class Uart{
	
	public:

	    enum uart_state_t{
		UART_OK,
		UART_FAILED
	    };

	    enum uart_number_t{
		UART_0,
		UART_1,
		UART_2,
		UART_NUMBER
	    };

	    enum uart_speed_t{
		S_9600,
		S_38400,
		S_57600,
		S_115200,
		S_NUMBER
	    };

	    Uart();
	    virtual ~Uart();
	    uart_state_t init(uart_number_t, uart_speed_t);
	    uart_state_t sendData(uint8_t*, uint16_t);
	    uart_state_t receiveData(uint8_t*, uint16_t);
            uart_state_t setBaudRate(uart_speed_t);
    };
}

#endif