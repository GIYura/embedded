/*
Circular buffer test
1. Fill the buffer with loop index.
2. Retrieve items and print
*/
#include <stdio.h>
#include "buffer.h"

#define BUFF_SIZE 55

static int buff[BUFF_SIZE + 1];

int main(int argc, char* argv[])
{
    BufferInit(buff, sizeof(buff) / sizeof(buff[0]));
    
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
