#include <stdio.h>

int main(int argc, char* argv[])
{
    register int value = 10;
    printf("Value: %d\n", value);

/*
К переменной объявленной с ключевым словом resister нельзя 
применить операцию взятия адреса (&).
*/
/* Error: won't compile */
    printf("Value address: %p\n", &value);

    return 0;
}
