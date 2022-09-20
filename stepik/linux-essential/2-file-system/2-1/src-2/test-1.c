#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main (void)
{
	int fd;
	char c;

	fd = open("test-1.txt", O_RDONLY);

	if (fd == -1)
	{
		fprintf(stderr, "Не могу открыть файл\n");
		return 1;
	}

	while (read (fd, &c, 1) > 0)
	{
		printf("%c", c);
	}

	close(fd);
	return 0;
} 
