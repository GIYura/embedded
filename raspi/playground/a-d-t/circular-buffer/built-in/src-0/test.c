/*
Circular Buffer Test.

1. Fill the buffer with loop indexs until it is full.
2. Retreive items from buffer and print them
 
*/
#include <stdio.h>
#include "buffer.h"

int main(int argc, char* argv[])
{
    BufferInit();
    
    for (int i = 0; i < 5000; i++)
    {
        if (!BufferPut(i))
        {
            break;
        }
    }

    printf("Buffer: ");

    for (int i = 0; i < 1000; i++)
    {
        int item;
        if (!BufferGet(&item))
        {
            break;
        }
        else
        {
            printf("%d ", item);
        }
    }
    printf("\n");
    
    return 0;
}
