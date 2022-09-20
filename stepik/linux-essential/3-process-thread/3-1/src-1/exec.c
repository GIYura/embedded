#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main (void)
{
	char * args[] = { "ls", "/", NULL};

	pid_t r = fork();
	if (r == 0) 
	{
		execve("ls", args, NULL);
	}
	return 0;
}
