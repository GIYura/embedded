#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* value = (char*)getenv("USER");	
	printf("USER = %s\r\n", value);

	value = getenv("HOME");
	printf("HOME = %s\r\n", value);

	value = getenv("PATH");
	printf("PATH = %s\r\n", value);

	putenv("DIR=/etc");
	setenv ("DIR", "/home/den", 1);
	value = (char*) getenv("DIR");
	printf("DIR = %s\n", value);
	unsetenv("DIR");

	return 0;
}
