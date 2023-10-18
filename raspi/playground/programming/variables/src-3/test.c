#include <stdio.h>

int main(int argc, char* argv[])
{
    int n = 10;
    int buffer[n];

    for (int i = 0; i < n; i++)
    {
        buffer[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    return 0;
}
