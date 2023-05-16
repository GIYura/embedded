#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE	20

static int getTime(const char* const dev, char* const buff, int buffSize);
static int bcd_to_decimal(unsigned char x);

int main(int argc, char* argv[])
{
	char timeBuff[BUFF_SIZE];

	if (argc < 2)
	{
		printf("Device file not found\n");
		return -1;
	}

	if (getTime(argv[1], timeBuff, sizeof(timeBuff)) == 0)
	{
        printf("Time [HH:MM:SS]: %d %d %d\n", bcd_to_decimal(timeBuff[0]),
                                              bcd_to_decimal(timeBuff[1]),
                                              bcd_to_decimal(timeBuff[2]));
	}
    else
    {
        printf("File %s does not exist\n", argv[1]);
    }
	
    return 0;
}

static int getTime(const char* const dev, char* const buff, int buffSize)
{
	int fd, ret = -1;
	fd = open(dev, O_RDWR);
	if (fd >= 0)
	{
		int res = read(fd, buff, buffSize);
		if (res > 0)
		{
			ret = 0;
		}
		else 
		{
			ret = -2;
		}
		close (fd);
	}

	return ret;
}

static int bcd_to_decimal(unsigned char x)
{
    assert(((x & 0xF0) >> 4) < 10);
    assert((x & 0x0F) < 10);

    int dec = ((x & 0xF0) >> 4) * 10 + (x & 0x0F);
    return dec;
}
