#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main (void)
{
	int fdesc;
	mode_t modes = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
	fdesc = creat("test-1.txt", modes);

	if (fdesc == -1)
	{
		fprintf(stderr, "Ошибка при создании файла\n");
		return 1;
	}

	close(fdesc);
	return 0;
}
