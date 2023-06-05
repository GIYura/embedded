/*
Exporing arrays & pointers
*/
#include <stdio.h>

int main (int argc, char* argv[])
{
    int buff[10] = {1,2,99,4,5,6,100};
    int *p, *q;
    int i;
/*
Add interger to a pointer
*/
/* meaning is the same  */
#if 0
    p = &buff[3];
#else
    p = buff + 3;
#endif
    printf("p points to %d\n", *p);

    q = p + 1;
    printf("q points to %d\n", *q);

/*
Subtract integer from a pointer
*/
    p = buff + 6;
    printf("p points to %d\n", *p);
    
    q = p - 3;
    printf("q points to %d\n", *q);

/*
Subtract pointer from pointer
NOTE: distance between 2 buffer elements in items, not in bytes
*/
    p = buff + 6;
    printf("p points to %d\n", *p);
    printf("p address: %p\n", p);
    q = buff + 2;
    printf("q points to %d\n", *q);
    printf("q address: %p\n", q);
    i = p - q;
    printf("distance between p and q in items: %d\n", i);
    printf("distance between p and q in bytes: %d\n", i * sizeof(int));

/*
Pointers comparison
*/
    p = buff + 6;
    q = buff + 1;

    if (p == q)
    {
        printf("p = q\n");
    }
    else if (p > q)
    {
        printf("p > q\n");
    }
    else if (p < q)
    {
        printf("p < q\n");
    }

/*
Compound literals. Составные литералы (C99).
Литерал - это константа которая не является символической
*/
    int* ptr = (int [2]) {10, 20};
    printf("%d %d\n", ptr[0], ptr[1]);

    int ref[] = {8,4,0,2};
    int* ptrRef;
    int index;

    for (index = 0, ptrRef = ref; index < 4; index++, ptrRef++)
    {
        printf("%d %d\n", ref[index], *ptrRef);
    }

    printf("%p\n", ref);
    printf("%p\n", &ref[0]);
    printf("%p\n\n\n", &ref[1]);

/**/
    int b[5] = {11,22,33,44,55};
    printf("Start %p End %p\n", &b[0], &b[4]);
    printf("address b: %p\n", b);
    printf("address b+1: %p\n", b+1);
    printf("address &b: %p\n", &b);
    printf("address (int*)(&b+1): %p\n", (int*)(&b)+1);
    printf("address &b+1: %p\n", &b+1);
    
    printf("%d bytes\n", sizeof(b));
    printf("%d bytes\n", sizeof(&b));
    
    //printf("%d\n", *b);
    //printf("%d\n", *((int*)(b+1)));
    //printf("%d\n", *((int*)(b)+1));
    return 0;
}
