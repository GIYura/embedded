/*
Exploring const qualifier
*/

#include <stdio.h>

static void PrintBuffer_NoConst(char* buff, unsigned int size);
static void PrintBuffer_ConstPointer(char* const buff, unsigned int size);
static void PrintBuffer_ConstData(const char* buff, unsigned int size);
static void PrintBuffer_ConstDataConstPointer(const char* const buff, unsigned int size);
static const char* GetMessage(void);

int main (int argc, char* argv[])
{
/* ERROR: not possible to change cosnt var directrly */
#if 0
    const int value = 1000;
    value = 101;
#endif
/* But it is possible to change it over non-const pointer.
BUT, this is possible if -Werror is not specified.
This will generate warning in all cases. */
    const int value = 1000;
    int* ptr = &value;
    *ptr = 101;
    printf("%d\n", value);

    char buff[] = { 'a','b','c','d','e','f','g','h' };
    PrintBuffer_NoConst(buff, sizeof(buff) / sizeof(buff[0]));
    PrintBuffer_ConstPointer(buff, sizeof(buff) / sizeof(buff[0]));
    PrintBuffer_ConstData(buff, sizeof(buff) / sizeof(buff[0]));
    PrintBuffer_ConstDataConstPointer(buff, sizeof(buff) / sizeof(buff[0]));

    return 0;
}

static void PrintBuffer_NoConst(char* buff, unsigned int size)
{
    printf(">>> Pointer and data are not Const\n");
    
/* Possible to change any item in the buffer */
    buff[0] = 'z';

/* Original pointer not changed, ptr looks at the same addres */
/*    
    char* ptr = buff;
*/

/* Possible 
    char a = 'a';
    buff = &a;
*/ 
    for (unsigned int i = 0; i < size; i++)
    {
        printf("%c ", *buff++); /* possible to increment pointer address */
    }
    printf("\n");
}

static void PrintBuffer_ConstPointer(char* const buff, unsigned int size)
{
    printf(">>> Pointer Const\n");

/* Possible to chanhe any item in the buffer */
    buff[1] = 'x';

/* This is ok, original pointer not changed, ptr looks ath the same address */
    char* ptr = buff; // ok

/* ERROR: not possible to change original pointer */
/*    
    char a = 'a';
    buff = &a;
*/

    for (unsigned int i = 0; i < size; i++)
    {
        printf("%c ", *ptr++);

/* ERROR: not possible to change const pointer
        printf("%c ", *buff++);
*/
    }
    printf("\n");
}

static void PrintBuffer_ConstData(const char* buff, unsigned int size)
{
    printf(">>> Data Const\n");

/* ERROR: Impossible to change data in the buffer */
/*
    buff[2] = 'y';
*/
/* Possible to change original pointer */
    char b = 'b';
    buff = &b;

/* ERROR: not possible to re-assign const pointer to non-const pointer. 
This leads to ponential change of the data */
#if 0
    char* ptr = buff;
#endif
/* Possible */
    const char* ptr = buff;

    for (unsigned int i = 0; i < size; i++)
    {
        /* possible to increment original pointer */
        printf("%c ", *ptr++);
#if 0
        printf("%c ", *buff++);
#endif
    }
    printf("\n");
}

static void PrintBuffer_ConstDataConstPointer(const char* const buff, unsigned int size)
{
    printf(">>> Pointer and Data Const\n");
/* ERROR: not possible change data */
/*
    buff[3] = 'w';
*/
/* ERROR: not possible to re-assign const pointer to non-const pointer.
This leads to potential data change. */
#if 0
    char* ptr = buff;
#endif
/* Possible */
    const char* ptr = buff;

/* Possible to re-assign original pointer, but not possible to increment it */
//    const char* const ptr = buff;

    for (unsigned int i = 0; i < size; i++)
    {
        /* Possible to increment pointer */
        printf("%c ", *ptr++);
        /* Possible */
        //printf("%c ", buff[i]);
        /* ERROR: not possible to increment original pointer */
        //printf("%c ", *buff++);
    }
    printf("\n");

/* 
Returning pointer to a const char is possible for string literal ONLY.
 */
    const char* message = GetMessage();
    printf("%s", message);
}

static const char* GetMessage(void)
{
    return "Hello C\n";
}
