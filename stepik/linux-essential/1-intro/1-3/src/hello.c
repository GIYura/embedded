#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <dlfcn.h>

typedef void (*PrintMessage_t)(const char* msg);
static PrintMessage_t printMessage;

bool initLib()
{
	void* handle = dlopen("./libPrint.so", RTLD_LAZY);
	if (NULL == handle)
	{
		return false;
	}
	printMessage = (PrintMessage_t)dlsym(handle, "PrintMessage"); //(void(*)(const char* ))dlsym(handle, "PrintMessage");
	if (NULL == printMessage)
	{
		return false;
	}
	return true;
}

int main()
{
	if (initLib())
	{
		printMessage("Hello Lib In Runtime");
	}
	else
	{
		printf("Lib not found\n");
	}
	return 0;
}
