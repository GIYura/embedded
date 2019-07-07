#include "Fifo.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


Lib::Fifo::Fifo(uint16_t size){
    assert(size);
    buff = (uint8_t*)malloc(sizeof(uint8_t) * size);
    if(NULL == buff){
	printf("Error. Can't allocate memory for Fifo Buffer\n");
    }
    head = 0;
    tail = 0;
    this->size = size;
}

Lib::Ring::~Fifo(){

}

void Lib::Fifo::nextHead(void){
    head = (head + 1) % size;
}

void Lib::Ring::nextTail(void){
    tail = (tail + 1) % size;
}

bool Lib::Ring::isEmpty(void){
    return head == tail;
}

bool Lib::Ring::isFull(void){
    nextHead();
    return head == tail;
}

void Lib::Ring::pop(uint8_t* data){
    if(!isEmpty()){
	*data = buff[tail];
	nextTail();
    }
}

void Lib::Ring::push(uint8_t data){
    buff[head] = data;
    if(isFull()){
	nextTail();
    }
    nextHead();
