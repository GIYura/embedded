#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE(x) ((sizeof(x)) / (sizeof(x[0])))

static void PrintBuffer(const int* const buffer, int size);
static void PrintBuffer_1(int buffer[], int size);
static void ModifyBuffer(int* buffer, int size);
static void PrintReverse(int* buffer, int size);
static void Swap(int* buffer, int size);
static bool Find(int* buffer, int size, int k);

int main(int argc, char* argv[])
{
    int buffer[] = { 1, 2, 3, 4, 5 };

    //printf("%p\n", buffer);

    PrintBuffer(buffer, BUFFER_SIZE(buffer));

    //ModifyBuffer(buffer, BUFFER_SIZE(buffer));

    //printf("%p\n", buffer);

    //PrintBuffer_1(buffer, BUFFER_SIZE(buffer));

    //PrintReverse(buffer, BUFFER_SIZE(buffer));

    //Swap(buffer, BUFFER_SIZE(buffer));

    //PrintBuffer(buffer, BUFFER_SIZE(buffer));
    int value = 5;
    if (Find(buffer, BUFFER_SIZE(buffer), value))
    {
        printf("Value %d found\n", value);
    }
    else
    {
        printf("Value %d NOT found\n", value);
    }

    return 0;
}

static void PrintBuffer(const int* const buffer, int size)
{
    if (!size)
        return;

    for (int i = 0; i < size; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

static void PrintBuffer_1(int buffer[], int size)
{
    if (!size)
        return;

    for (int i = 0; i < size; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

static void ModifyBuffer(int* buffer, int size)
{
    int* pbuff = NULL;
    if (!size)
        return;
    
    pbuff = buffer;    

    for (int i = 0; i < size; i++)
    {
        if (pbuff != NULL)
            *pbuff++ = i + 10;
    }
    printf("\n");
}

static void PrintReverse(int* buffer, int size)
{
    printf("First item address: %p\n", buffer);
    
    int* pbuff = NULL;
    if (!size)
        return;

    pbuff = &buffer[size - 1];

    printf("Last item address: %p\n", pbuff);

    for(int i = 0; i < size; i++)
    {
        printf("%d ", *pbuff--);
    }
    printf("\n");
}


static void Swap(int* buffer, int size)
{
    if (!size)
        return;

    int* start = buffer;
    int* end = &buffer[size - 1];

#if 0
    while (start < (buffer + (size / 2)))
    {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
#endif
#if 0
    for (int i = 0; i < size / 2; i++)
    {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
#endif
#if 0
    for (int i = 0; i < (size / 2); i++)
    {
        int temp = buffer[i];
        buffer[i] = buffer[size - i - 1];
        buffer[size - i - 1] = temp;
    }
#endif
}

static bool Find(int* buffer, int size, int k)
{
    bool ret = false;

    if (!size)
        return false;

    for (int i = 0; i < size; i++)
    {
        if (k == buffer[i])
        {
            ret = true;
            break;
        }
    }

    return ret;
}
