#ifndef _RING_H
#define _RING_H

#include <stdint.h>

namespace Buffer{
    class Ring{

	    uint16_t head;
	    uint16_t tail;
	    uint8_t* buff;
	    uint16_t size;

	    void nextHead(void);
	    void nextTail(void);
	    bool isFull(void);
	    bool isEmpty(void);

	public:
	    Ring(uint16_t);
	    virtual ~Ring();

	    void pop(uint8_t*);
	    void push(uint8_t);
    };
}

#endif