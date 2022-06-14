#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 5

int main()
{
	FILE* pipe_fp;
	const char* fruits[MAX_STR] = { "pear", "banana", "orange", "plum", "apple" };

	printf("--- List before sort:\n");

	for (int i = 0; i < MAX_STR; i++)
	{
		printf("%s\n", fruits[i]);
	}

	if ((pipe_fp = popen("sort", "w")) == NULL)
	{
		perror("popen failed\n");
		exit (1);
	}
	
	printf("--- List after sort:\n");

	for (int i = 0; i < MAX_STR; i++)
	{
		fputs(fruits[i], pipe_fp);
		fputc('\n', pipe_fp);
	}

	pclose(pipe_fp);

	return 0;
}
