#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* ReturnStringLiteral(void);
static char* ReturnGlobalBuffer(void);
static char* ReturnStaticBuffer(void);
static char* ReturnDynamicallyAllocatedBuffer(void);
static void UseDynamicallyAllocatedBuffer(char* buffer, int size);

char message[] = "Hello WORLD";

int main(int argc, char* argv[])
{
#if 1
    char* str;
    str = ReturnStringLiteral();
    printf("%s\n", str);

    ReturnGlobalBuffer();
    printf("%s\n", message);
#endif
    char* s;
    s = ReturnStaticBuffer();
    printf("%s\n", s);

    char* ptr;
    ptr = ReturnDynamicallyAllocatedBuffer();
    printf("%s\n", ptr);

    char* pBuffer = (char*)malloc(20 * sizeof(char));
    if (!pBuffer)
        return -1;

    UseDynamicallyAllocatedBuffer(pBuffer, 20);
    printf("%s\n", pBuffer);
    free(pBuffer);

    return 0;
}

static char* ReturnStringLiteral(void)
{
/* NOTE: works for string ONLY */
    return "Hello World";
}

static char* ReturnGlobalBuffer(void)
{
    message[0] = 'A';
    return message;
}
 
static char* ReturnStaticBuffer(void)
{
    static char buffer[10];
    
    buffer[0] = 'A';
    buffer[1] = 'B';
    buffer[2] = 'C';
    buffer[3] = 'D';
    buffer[4] = 'E';

    return buffer;
}

static char* ReturnDynamicallyAllocatedBuffer(void)
{
    char* buffer = (char*)malloc(10 * sizeof(char));
    
    buffer[0] = 'F';
    buffer[1] = 'F';
    buffer[2] = 'F';
    buffer[3] = '\0';

    return buffer;
}

static void UseDynamicallyAllocatedBuffer(char* buffer, int size)
{
/* best solution */
#if 0
    for (int i = 0; i < size - 1; i++)
    {
        buffer[i] = 'B';
    }
    buffer[size] = '\0';
#endif
    strncpy(buffer, "This is a string", size);
}
