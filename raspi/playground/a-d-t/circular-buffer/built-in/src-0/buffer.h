#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>

void RingInit(void);
void RingDeinit(void);
bool RingEnqueue(int item);
bool RingDequeue(int* item);

#endif /* BUFFER_H */
