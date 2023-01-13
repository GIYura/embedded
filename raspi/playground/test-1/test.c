#include <stdio.h>

int main()
{
	printf("char = %d\n", sizeof(char));
	printf("short = %d\n", sizeof(short));
	printf("int = %d\n", sizeof(int));
	printf("long = %d\n", sizeof(long));
	printf("long long = %ld\n", sizeof(long long));
	printf("float = %d\n", sizeof(float));
	printf("double = %d\n", sizeof(double));

	printf("char* = %d\n", sizeof(char*));
	printf("short* = %d\n", sizeof(short*));
	printf("int* = %d\n", sizeof(int*));
	printf("long* = %d\n", sizeof(long*));
	printf("long long* = %ld\n", sizeof(long long*));
	printf("float* = %d\n", sizeof(float*));
	printf("double* = %d\n", sizeof(double*));

	return 0;
}
