# 1 "test.c"
# 1 "/home/jura/embedded/raspi/playground/programming/performance//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "test.c"



int main(int argc, char* argv[])
{
    volatile int x;

    if (__builtin_expect(argc % 2, 1))
    {
        x = 1;
    }
    else
    {
        x = 0;
    }

    return x;
}
