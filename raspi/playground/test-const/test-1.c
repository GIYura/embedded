#include <stdio.h>

static void PrintBuffer_0(char* buff, unsigned int size);
static void PrintBuffer_1(char* buff, unsigned int size);
static void PrintBuffer_2(char* const buff, unsigned int size);
static void PrintBuffer_3(const char* buff, unsigned int size);
static void PrintBuffer_4(const char* const buff, unsigned int size);

static void PrintStr(char* buff);
static void FillStr(char* buff);
static void Fill(char** buff);

static void foo(void)
{
    int x = 1;
}

static void bar(void)
{
    int x;
    printf("x: %d\n", x);
}


int main (int argc, char* argv[])
{
    foo();
    bar();

    return 0;


    int value = 10;
    int ret = printf("%d\n", value);
    printf("ret = %d\n", ret);
#if 0
    return ret;


    char str[] = "Hello";
    PrintStr(str);
    
    char strBuff[20];
    FillStr(strBuff);
    PrintStr(strBuff);

    char* ptrStr;
    char s[10];
    ptrStr = &s;
    Fill(&ptrStr);
    PrintStr(s);

    return 0;

    char buff_1[] = { 1,2,3,4,5,6,7,8,9 };
    PrintBuffer_0(buff_1, sizeof(buff_1) / sizeof(buff_1[0]));
    PrintBuffer_1(buff_1, sizeof(buff_1) / sizeof(buff_1[0]));
    PrintBuffer_0(buff_1, sizeof(buff_1) / sizeof(buff_1[0]));

    char buff_2[] = { 9,8,7,6,5,4,3,2,1, };
    PrintBuffer_2(buff_2, sizeof(buff_2) / sizeof(buff_2[0]));

    char buff_3[] = { 11,22,33,44,55,66,77,88 };
    PrintBuffer_3(buff_3, sizeof(buff_3) / sizeof(buff_3[0]));

    char buff_4[] = { 66,22,11 };
    PrintBuffer_4(buff_4, sizeof(buff_4) / sizeof(buff_4[0]));

    return 0;
#endif
}

#if 0

static void PrintBuffer_1(char* buff, unsigned int size)
{
    buff[0] = 0xaa;
    char* ptr = buff;
    
    for (unsigned int i = 0; i < size; i++)
    {
        printf("%d ", *ptr++);
    }
    printf("\n");
}

static void PrintBuffer_2(char* const buff, unsigned int size)
{
    buff[1] = 0xbb; //ok
    char* ptr = buff; // ok

    for (unsigned int i = 0; i < size; i++)
    {
        printf("%d ", *ptr++);
    }
    printf("\n");
}

static void PrintBuffer_3(const char* buff, unsigned int size)
{
    //buff[2] = 0xcc;   // ERROR
    char* ptr = buff; // ok, but warning, if -Werror, will be error

    for (unsigned int i = 0; i < size; i++)
    {
        printf("%d ", *ptr++);
    }
    printf("\n");
}

static void PrintBuffer_4(const char* const buff, unsigned int size)
{
    //buff[3] = 0xff;   //ERROR
    char* ptr = buff; // ok, but warning, if -Werror, will be error
    //const char* ptr = buff; // ERROR: conflicting type of ptr
    //const char* const ptr = buff; // ERROR: conflicting type of ptr

    for (unsigned int i = 0; i < size; i++)
    {
        printf("%d ", *ptr++);
    }
    printf("\n");
}

static void PrintBuffer_0(char* buff, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        printf("%d ", buff[i]);
    }
    printf("\n");
}

static void PrintStr(char* str)
{
    while (*str != '\0')
    {
        printf("%c ", *str++);
    }
    printf("\n");
}

static void FillStr(char* buff)
{
    *buff++ = 'a';
    *buff++ = 'b';
    *buff++ = 'c';
    *buff = '\0';
}

static void Fill(char** buff)
{
    *buff++ = 'n';
    *buff = '\0';
}
#endif
