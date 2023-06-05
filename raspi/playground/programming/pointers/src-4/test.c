/*
Difference between array and pointer
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
/*
message - это адрес где хранится начало данные. т.е 
прибавив к этому адресу некий индекс можно получить нужные данные.
Пример:
message = 0x1000
index  = 5
0x1000 + 5 получим значание по адресу 0х1005

pMessage - это адрес, по которому лежит некое значение, которое 
в свою очередь хранит адрес начала данных. Именно к нему прибавив
индекс можно получить доступ к данным.
Пример:
pMessage = 0x1000
index = 5
нужно выяснить какое значение лежит по адресу 0х1000. Например: 0х2000.
Далее, к 0х2000 + index и получить данные по адресу 0х2005.
*/
    char message[] = "Hello";
    char* pMessage = "Hello";

    char hello[] = "HELLO";

    message[3] = 'a';
/*
    char message[] access:
1. get base address of an array
2. add index to the base address
3. get the contents from base address + index

    char* pMessage access:
1. get the contents from address
2. add index to that address
3. get content from address + index
*/
/*
ERROR: string literal locates in READ-ONLY memory.
Modifying RO memory will lead to segmentation fault.
*/
#if 0
    pMessage[3] = 'a';
#endif

    pMessage = hello;
    memcpy(message, hello, sizeof(hello));

    printf("%s %s\n", message, pMessage);

    return 0;
}
