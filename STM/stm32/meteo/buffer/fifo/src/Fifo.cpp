#include "Fifo.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


Buffer::Fifo::Fifo(uint16_t size){
    assert(size);
    buff = (uint8_t*)malloc(sizeof(uint8_t) * size);
    if(NULL == buff){
	printf("Error. Can't allocate memory for Fifo Buffer\n");
    }
    head = 0;
    tail = 0;
    this->size = size;
}

Buffer::Fifo::~Fifo(){

}

void Buffer::Fifo::nextHead(void){
    head = (head + 1) % size;
}

void Buffer::Fifo::nextTail(void){
    tail = (tail + 1) % size;
}

bool Buffer::Fifo::isEmpty(void){
    return head == tail;
}

bool Buffer::Fifo::isFull(void){
    nextHead();
    return head == tail;
}

void Buffer::Fifo::pop(uint8_t* data){
    if(isEmpty()){
	return;
    }
    *data = buff[tail];
    nextTail();
}

void Buffer::Fifo::push(uint8_t data){
    
    if(isFull()){
	return;
	
    }
    buff[head] = data;
    nextHead();
}