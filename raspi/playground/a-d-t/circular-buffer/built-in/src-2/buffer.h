#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>

void RingInit(void* buff, int itemSize, int count);
void RingDeinit(void);
bool RingEnqueue(void* item, int size);
bool RingDequeue(void* item, int size);

#endif /* BUFFER_H */
