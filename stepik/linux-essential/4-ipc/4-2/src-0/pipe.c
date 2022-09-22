#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int fd[2]; /* buffer to store file descriptors; fd[0] - read; fd[1] - write */
	pid_t childpid;
	int nbytes;
	char message[] = "hello world via pipe\n";
	char readBuff[50];

	pipe(fd);
	if ((childpid = fork()) == -1)
	{
		perror("Fork Failed\n");
		exit(1);
	}
	
	/* child pid == 0 in child process  */
	if (childpid == 0)
	{
		close(fd[0]);	/* child process closes input side of pipe */
		write(fd[1], message, strlen(message));
	}
	else
	{
		close(fd[1]);	/* parent process closes output side of pipe */
		nbytes = read(fd[0], readBuff, sizeof(readBuff));
		printf("Received: %d bytes\n", nbytes);
		printf("Received: %s\n", readBuff);
	}
	return 0;
}
