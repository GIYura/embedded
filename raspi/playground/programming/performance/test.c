
/**/

int main(int argc, char* argv[])
{
    volatile int x;

    if (__builtin_expect(argc % 2, EXPECT))
    {
        x = 1;
    } 
    else 
    {
        x = 0;
    }

    return x;
}
#if 0
int main(int argc, char* argv[])
{
    if (__builtin_expect(argc, 1))
    {
        a++;
        return -1;
    }

    b++;
    
    return 0;
}
#endif
