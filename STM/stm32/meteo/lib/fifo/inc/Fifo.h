#ifndef _FIFO_H
#define _FIFO_H

#include <stdint.h>

namespace Lib{
    class Fifo{

	    uint16_t head;
	    uint16_t tail;
	    uint8_t* buff;
	    uint16_t size;

	    void nextHead(void);
	    void nextTail(void);
	    bool isFull(void);
	    bool isEmpty(void);

	public:
	    Fifo(uint16_t);
	    virtual ~Fifo();

	    void pop(uint8_t*);
	    void push(uint8_t);
    };
}

#endif
