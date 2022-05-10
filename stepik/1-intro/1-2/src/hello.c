#include <unistd.h>
#include <stdio.h>
#include "print.h"

int main()
{
	printf("VALUE = [%d]\n", VALUE);

	int counter = 0;
	while(1)
	{
		counter++;
		PrintMessage("Hello World!");
		sleep(1);
	}
	return 0;
}
