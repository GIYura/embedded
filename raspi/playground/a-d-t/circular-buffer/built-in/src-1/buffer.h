#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>

void BufferInit(int* buff, int buffSize);
void BufferDeinit(void);

/*
Put an item to the buffer
*/
bool BufferPut(int item);

/*
Get an item from the buffer
*/
bool BufferGet(int* item);

#endif /* BUFFER_H */
