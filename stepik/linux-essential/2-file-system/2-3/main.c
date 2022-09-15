#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int c, const char **v)
{
	char buff[100];
	size_t sz = 0;

	if (c != 2)
	{
		printf("Please pass %s filename\n", v[0]);
		return -1;
	}

	int fd = open(v[1], O_RDONLY | O_NOFOLLOW);
	perror("fd");
	printf("fd = %d\n", fd);
	sz = read(fd, buff, sizeof(buff));
	printf("sz = %ld\n", sz);

	return 0;
}
