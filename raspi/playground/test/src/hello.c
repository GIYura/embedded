#include "print.h"
#include <unistd.h>

#define SLEEP_TIME 1 /* sec */

int main()
{
	int value = 10;
	int* pValue = &value;
	printf("Value = [%d]\r\n", *pValue);

	while (1)
	{
		PrintMessage("Hello Raspberry Pi 4");
		sleep(SLEEP_TIME);
	}

	return 0;
}
