#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <unistd.h>

#define STACK_SIZE 10000
char childStack[STACK_SIZE + 1];

int child(void* params)
{
	int c = 0;
	while(1)
	{
		usleep(50000);
		printf("child %d\n", c++);
	}
}

int main()
{
	int c = 0;
	int res = clone(child, childStack + STACK_SIZE, CLONE_PARENT, 0);
	printf("clone res = %d\r", res);

	while (1)
	{
		usleep(50000);
		printf("parent %d\n", c++);
	}	
	return 0;
}
