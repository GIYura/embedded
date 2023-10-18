#include <stdio.h>

int main(int argc, char* argv[])
{
    char msg[] = "Hello";
    char* msg1 = "World";

    printf("%d %d\n", sizeof(msg), sizeof(msg1));
    printf("%d %d\n", sizeof(*msg), sizeof(*msg1));

    char buff[] = "Surprised";
    char* pbuff = "Surprised";

    printf("%c %c\n", buff[3], pbuff[3]);
    printf("%p %p\n", buff, pbuff);

    int arr[] = { 1, 2, 3 };
    printf("\nBase address: %#x\n", arr);
    printf("Base address &: %#x\n", &arr);
    printf("Base address + 1: %#x\n", arr + 1);
    printf("Address of the whole array + 1: %#x\n", &arr + 1);
    printf("Size of array: %#x\n", sizeof(arr));

    return 0;
}
