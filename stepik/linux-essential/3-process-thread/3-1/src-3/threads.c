#include <stdio.h>
#include <unistd.h>
#include <pthread.h> /* Подключаем для работы с потоками */

static void* thread1(void* arg)
{
	int value = *(int*) arg;
	printf("\nThread 1: %d\n", value);
	sleep(1);	/* Засыпаем на 5 секунд */
	pthread_exit(NULL);
}

static void* thread2(void* arg)
{
	int value = *(int*) arg;
	printf("\nThread 2: %d\n", value);
	sleep(10);	/* Засыпаем на 10 секунд */
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t tid1;
	pthread_t tid2;
	int t_arg;
	
	t_arg = 1;
	pthread_create(&tid1, NULL, &thread1, &t_arg);
	
	t_arg = 5;
	pthread_create(&tid2, NULL, &thread2, &t_arg);
	
	while (1);
	return 0;
}

