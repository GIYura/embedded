#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>

void read_and_report(int fd)
{
	char buff[100];
	printf("FD %d is ready to read\n", fd);
	int bytes = read(fd, buff, 100);
	buff[bytes] = 0;
	printf("Get %d from %d : %s\n", bytes, fd, buff);
}

/**/
int main(int argc, char* argv[])
{
	int f1 = open("./f1.fifo", O_RDWR);
	int f2 = open("./f2.fifo", O_RDWR);

	if (!f1 && !f2)
	{
		printf("Error\n");
		return 0;
	}

	printf("F1 = %d\n", f1);
	printf("F2 = %d\n", f2);

	fd_set readSet;

	while (1)
	{
		FD_ZERO(&readSet);
		FD_SET(f1, &readSet);
		FD_SET(f2, &readSet);

		int result = select(f2+1, &readSet, NULL, NULL, NULL);
		if (result)
		{
			if (FD_ISSET(f1, &readSet))
			{
				read_and_report(f1);
			}

			if (FD_ISSET(f2, &readSet))
			{
				read_and_report(f2);
			}
		}
	}
	
	return 0;
}
