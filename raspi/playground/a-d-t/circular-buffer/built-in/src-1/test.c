#include <stdio.h>
#include "buffer.h"

#define BUFF_SIZE 55

static int buff[BUFF_SIZE + 1];

int main(int argc, char* argv[])
{
    RingInit(buff, sizeof(buff) / sizeof(buff[0]));
    
    for (int i = 0; i < 5000; i++)
    {
        if (!RingEnqueue(i))
            break;
    }

    for (int i = 0; i < 1000; i++)
    {
        int item;
        if (!RingDequeue(&item))
            break;
        else
            printf("%d ", item);
    }
    printf("\n");
    
    return 0;
}
