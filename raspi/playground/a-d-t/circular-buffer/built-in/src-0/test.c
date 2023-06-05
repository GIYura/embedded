#include <stdio.h>
#include "buffer.h"

int main(int argc, char* argv[])
{
    RingInit();
    
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
            printf("%d", item);
    }
    printf("\n");
    
    return 0;
}
