/*
Basics of pointers
*/

#include <stdio.h>

#define ENDIANNESS      1
#define SWAP_NIBBLES    1
#define BASICS          1

int main(int argc, char* argv[])
{
#if BASICS
    printf(">>> Basics Start\n");
   
    printf("Sizeof char: %d\n", sizeof(char));
    printf("Sizeof short: %d\n", sizeof(short));
    printf("Sizeof int: %d\n", sizeof(int));
    printf("Sizeof long int: %d\n", sizeof(long int));
    printf("Sizeof long long int: %d\n", sizeof(long long int));
    printf("Sizeof double: %d\n", sizeof(double));
    printf("Sizeof float: %d\n", sizeof(float));
    printf("Sizeof char*: %d\n", sizeof(char*));
    printf("Sizeof short*: %d\n", sizeof(short*));
 
    /* int value */
    int value = 10;

    /* pValue is a pointer to an int
    NOTE: stores value address */
    int* pValue = &value;   

    /* ptrValue is a pointer to an int
    NOTE: stores value address.
    Many pointers can point to the same value, 
    there is no restriction  */
    int* ptrValue = &value;

    printf ("Value: %d\n", value);
    printf ("Value address: %p\n", pValue);
    printf ("Value address: %p\n", ptrValue);

/* Here p and q are pointers to an int */
    int* p, *q;
    p = &value;
    q = &value;

/* Here p is a pointer to an int, q is just an int 
NOTE: won't be able to compile ths code
*/
#if 0
    int* p, q;
    p = &value;
    q = &value;
#endif

    int i = 11, j = 33;
    printf("i = %d j = %d\n", i, j);
    int *pi, *pj;

    pi = &i;
    pj = &j;
    printf("pi = %d pj = %d\n", *pi, *pj);
    printf("pi = %p pj = %p\n", pi, pj);

#if 0
/* assign the address; pointer assignment */
    pi = pj;
    printf("i = %d j = %d\n", *pi, *pj);
    printf("pi = %p pj = %p\n", pi, pj);
#else
/* assign the content of the address */
    *pi = *pj;
    printf("i = %d j = %d\n", *pi, *pj);
    printf("pi = %p pj = %p\n", pi, pj);
    printf(">>> Basics End\n");
#endif
#endif /* BASICS */

#if ENDIANNESS 
    printf(">>> Endianness Start\n");
    
    /* declare 2 byte variable */
    unsigned short x = 0x0001;
    /* declare pointer to char.
    NOTE: pointer stores var address type-casted to char*
     */
    unsigned char* px = (unsigned char*)&x;
    
    /* print base address of the variable */
    printf("Base address of variable: %p\n", px);
    /* print value stored in base address */
    printf("Value stored in base address: %d\n", *px);
    /* print base address + offset
    NOTE:
    - (&x) + 1 - сместить базовый адрес на 1 байт
    - (&x + 1) - сместить базовый адрес на 1 элемент,
    при этом элемент может быть массив (структура ...) т.е.
    смещение произойдет за границы элемента
     */
    printf("Shifted by 1: %p\n", (unsigned char*)(&x) + 1);
    /* print value stored in based address + offset */
    printf("Value stored in shifted address: %d\n", *((unsigned char*)(&x) + 1));

    /* проверка значения по базовому адресу */
    if (*px)
    {
        /* NOTE: если по базовому (младшему адресу) храниться 1 (LSB), то
        это LITTLE
        00  01 - value
          \/
          /\
        100 101 - address
         */
        printf("LITTLE\n");
    }
    else 
    {
        /* NOTE: иначе BIG
        00  01 - value
        |   |
        100 101 - address
         */
        printf("BIG\n");
    }

    printf(">>> Endianness End\n");
#endif /* ENDIANNESS */

#if SWAP_NIBBLES
    printf (">>> Swap nibbels Start\n");

    unsigned short origValue = 0x1234;
    unsigned short swapValue = 0x0000;
    printf("Original value: %#x\n",origValue);
    unsigned char* origValueLo = ((unsigned char*)(&origValue) + 1);
    unsigned char* origValueHi = (unsigned char*)(&origValue);

    printf("HIGH address = %p\n", origValueHi);
    printf("LOW address = %p\n", origValueLo);
 
    printf("Value of HIGH = %#x\n", *origValueHi);
    printf("Value in LOW = %#x\n", *origValueLo);

    swapValue = (*origValueHi << 8) | *origValueLo;

    printf("Swapped value: %#x\nNOTE: this is how value stored in memory\n", swapValue);

    printf(">>> Swap nibbles End\n");
#endif /* SWAP_NIBBLES */

    return 0;
}
