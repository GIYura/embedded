#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BUFF_SIZE	20
#define RTC_READ_ONLY 0

typedef enum
{
    RTC = 0,
    SYS,
} TIME_T;

static int RtcGetTime(const char* const dev, char* const buff, int buffSize);
static int RtcSetTime(const char* const dev, char* const buff, int buffSize);
static void SystemTimeGet(struct tm* t);
static int bcdToDec(unsigned char val);
static void TimePrint(const char* const buff, TIME_T time);
static struct tm systemTime;

int main(int argc, char* argv[])
{
    char timeBuff[BUFF_SIZE];

    if (argc < 2)
    {
        printf("Invalid argument\n");
        return -1;
    }
#if RTC_READ_ONLY
    SystemTimeGet(&systemTime);

    timeBuff[2] = systemTime.tm_sec;
    timeBuff[1] = systemTime.tm_min;
    timeBuff[0] = systemTime.tm_hour; 

    if (RtcSetTime(argv[1], timeBuff, sizeof(timeBuff)) == 0)
    {
        TimePrint(timeBuff, SYS);
    }
    else
    {
        printf("File %s does not exist\n", argv[1]);
        return -1;
    }
#endif
    if (RtcGetTime(argv[1], timeBuff, sizeof(timeBuff)) == 0)
    {
        TimePrint(timeBuff, RTC);
    }

    return 0;
}

static void SystemTimeGet(struct tm* t)
{
    time_t ti = time(NULL);
    struct tm tm = *localtime(&ti);
    t->tm_hour = tm.tm_hour;
    t->tm_min = tm.tm_min;
    t->tm_sec = tm.tm_sec;
}

static int RtcGetTime(const char* const dev, char* const buff, int buffSize)
{
    int fd; 
    int ret = -1;

    fd = open(dev, O_RDONLY);
    if (fd >= 0)
    {
        if (read(fd, buff, buffSize) > 0)
        {
            ret = 0;
        }
        close (fd);
    }

    return ret;
}

static int RtcSetTime(const char* const dev, char* const buff, int buffSize)
{
    int fd; 
    int ret = -1;

    fd = open(dev, O_WRONLY);
    if (fd >= 0)
    {
        if (write(fd, buff, buffSize) > 0)
        {
            ret = 0;
        }
        close (fd);
    }
    return ret;
}

static int bcdToDec(unsigned char val)
{
#if 0
    return (val / 16) * 10 + (val % 16);
#else
    int dec = ((val & 0xF0) >> 4) * 10 + (val & 0x0F);
    return dec;
#endif
}

static void TimePrint(const char* const buff, TIME_T time)
{
    switch (time)
    {
        case RTC:
            printf("RTC time:\t");
        break;

        case SYS:
            printf("System time:\t");
        break;

        default: break;
    }
#if RTC_READ_ONLY
    printf("%02d:%02d:%02d\n", buff[0], buff[1], buff[2]);
#else
    printf("%02d:%02d:%02d\n", bcdToDec(buff[0]), 
                               bcdToDec(buff[1]), 
                               bcdToDec(buff[2]));
#endif
}
