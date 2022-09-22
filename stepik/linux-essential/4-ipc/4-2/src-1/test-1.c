#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *in;
//	extern FILE *popen();
	char buff[512];

	/* Создаем канал, вызываем программу ls, режим "r" */
	if (!(in = popen("ls", "r")))
	{
		exit(1);
	}

	/* Читаем вывод ls и отображаем его на экране */
	while (fgets(buff, sizeof(buff), in) != NULL ) 
	{
		printf("Output: %s\n", buff);
	}

	/* Закрываем канал */
	pclose(in);

	return 0;
}

