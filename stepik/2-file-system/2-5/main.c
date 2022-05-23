#include <stdio.h>

int* f()
{
	return (int*)12;
}

void print(int* v)
{
	printf("Value = %d\n", *v);
}

int main()
{
	print(f());
}
