#include <stdio.h>

/* внешняя переменная не известна main() и foo(), т.к. внутри
них она переопределеная. х будет известна любой другой функции,
в которой нет локальной переменной х. */
int x = 100;

void foo(void);

int main(int argc, char* argv[])
{
    /* локальная автоматическая переменная */
    int x;
    printf("inside main() x = %d\n", x);
    foo();
    return 0;
}
 
/* внешняя переменная известная только foo */
int y;
void foo(void)
{
    /* локаотная автоматическая переменная, объявленная явно */
    auto int x;
    printf("inside foo() x = %d\n", x);
    printf("inside foo() y = %d\n", y);
}
