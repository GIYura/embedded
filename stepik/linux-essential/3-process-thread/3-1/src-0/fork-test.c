#include <unistd.h>
#include <stdio.h>

int main (void)
{
	if (fork() == 0)
	{
		printf("Я дочерний процесс, PID = %d\n", getpid());
	}
	else
	{
		printf("Я родительский процесс, PID = %d\n", getpid());
	}
	sleep (10);
	return 0;
}

