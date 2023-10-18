#include <stdio.h>

void foo(void);

int main(int argc, char* argv[])
{
    foo();
    foo();
    foo();

    return 0;
}

void foo(void)
{
    /*
    Область видимости: блок
    Связывание: нет
    Продолжительность хранения: автоматическая
    */
    int x = 1;
    /*
    Область видимости: блок
    Связывание: нет
    Продолжительность хранения: статитеская
    */
    static int y = 1;
    printf("X = %d; Y = %d\n", x++, y++);
}
