#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

static float getTemp(const char* const dev);

//static char* name = "/dev/ds18b20";

int main(int argc, char *argv[])
{
    if (argc < 2)
	{
		printf("Device file NOT found\n");
		return 1;
	}
	
    float temperature = getTemp(argv[1]);
	printf("Temperature = %.2f C\n", temperature);

	return 0; 
}

float getTemp(const char* const devName)
{
    int fd;  
    unsigned char result[2] = {0};  
    unsigned int hightBitValue = 0;  
    unsigned int lowBitValue = 0;  
    float p = 0.0625;
    float value = 1024.0f;

    fd = open(devName, 0);  
    if (fd >= 0) 
    {
        int i = read(fd, &result, sizeof(&result));
        if (i >= 0)
        {
            hightBitValue = result[1];
            lowBitValue = result[0];
            hightBitValue <<= 8;
            hightBitValue = hightBitValue + lowBitValue;
            if ((result[1] & 0xf8))
            {
                hightBitValue = ~hightBitValue + 1;
                value = hightBitValue * p * -1;
            }
            else
            {
                value = hightBitValue * p;
            }

        }  
        close(fd);
    }
    return value;
}
