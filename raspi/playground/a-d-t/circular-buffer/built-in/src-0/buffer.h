#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>

void BufferInit(void);
void BufferDeinit(void);
/*
Put item in the buffer
*/
bool BufferPut(int item);

/*
Get an item from the buffer
*/
bool BufferGet(int* item);

#endif /* BUFFER_H */
