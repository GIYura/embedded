#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void mysignal_handler(int signalNo)
{
	printf("Called with %d\n", signalNo);
	return;
}

void signalPrint(int sigNo)
{
	printf("Signal Number: %d\n", sigNo);
}

int main()
{
	int counter = 0;

	signal(SIGINT, mysignal_handler);

#if 0
	signal(SIGTSTP, signalPrint);
#endif

	while (1)
	{
		printf("Hello %d\n", counter++);
		usleep(500000);
	}
	
	return 0;
}

