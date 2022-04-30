#include "print.h"

/**/
void PrintMessage(const char* const message)
{
	static int counter = 0;
	counter++;
	printf("[%d] %s\r\n", counter, message);
}
