#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
	int count = 0;

	if (fork() == 0)
	{
		count++;
		printf("Дочерний процесс, count = %d\n", count);
		return 0;
	}
	else
	{
		printf("Родительский процесс, count = %d\n", count);
	}
	return 0;
}

