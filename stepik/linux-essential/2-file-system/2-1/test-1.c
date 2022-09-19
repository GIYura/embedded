#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[])
{
	FILE *fp;
	int ch;
	if ((fp = fopen(argv[1], "r")) == NULL)
	{
		printf("Ошибка при открытии файла\n");
		exit(1);
	}

	while ((ch = fgetc(fp)) != EOF) 
	{
		printf("%c", (char)ch);
	}
	
	fclose(fp);
	return 0;
}
