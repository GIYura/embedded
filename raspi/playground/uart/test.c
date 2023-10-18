#if 0
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>

int main(int argc, char** argv) 
{
    int sfd = open("/dev/serial0", O_RDWR | O_NOCTTY);
    if (sfd == -1)
    {
        printf("Error no is : %d\n", errno);
        printf("Error description is : %s\n", strerror(errno));
        return (-1);
    };
    struct termios options;
    tcgetattr(sfd, &options);
    cfsetspeed(&options, B9600);
    cfmakeraw(&options);
    options.c_cflag &= ~CSTOPB;
    options.c_cflag |= CLOCAL;
    options.c_cflag |= CREAD;
    options.c_cc[VTIME] = 255;
    options.c_cc[VMIN] = 255;
    tcsetattr(sfd, TCSANOW, &options);
    char buf[] = "hello world";
    char buf2[11];
    int count = write(sfd, buf, 11);
    count = read(sfd, buf2, 11);
    buf2[11] = 0;
    printf("%s", buf2);
    close(sfd);
    return 0;
}
#endif

#if 1
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>

#define BUFF_MAX 1000   /* bytes */
#define OFFSET  10

static char writeBuff[] = "This is UART loop-back test!!!!!!!";
static char readBuff[BUFF_MAX] = "";

int main(int argc, char* argv[])
{
    printf("UART Loop-back test\n");
    printf("Baud rate: 9600\n");
    printf("Format: 8N1\n");

    int file = open("/dev/serial0", O_RDWR | O_NONBLOCK);
    if (file < 0)
    {
        printf("Can't open file\n");
        return -1;
    }

#if 0
    struct termios options;
    tcgetattr(file, &options);
    cfsetspeed(&options, B9600);
    cfmakeraw(&options);
    options.c_cflag &= ~CSTOPB;


    options.c_cflag |= CLOCAL;
    options.c_cflag |= CREAD;
    options.c_cc[VTIME] = 255;
    options.c_cc[VMIN] = 255;
    tcsetattr(file, TCSANOW, &options);
#endif

#if 1
    struct termios options;
    /* read existing settings */
    tcgetattr(file, &options);

    /* modify settings */
    options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
    
    //options.c_cc[VTIME] = 255;
    //options.c_cc[VMIN] = 255;

    /* apply settings */
    tcsetattr(file, TCSANOW, &options);

    write(file, writeBuff, sizeof(writeBuff) / sizeof(writeBuff[0]));

#if 1
    unsigned int delayUs = (strlen(writeBuff) + OFFSET) * 1000;
    printf("Delay: %d us\n", delayUs);
    usleep(delayUs);
#endif
#endif

    //write(file, writeBuff, sizeof(writeBuff) / sizeof(writeBuff[0]));

    int rd = read(file, readBuff, sizeof(writeBuff) / sizeof(writeBuff[0]));

    if (rd < 0)
    {
        printf("Can't read data, probably the loop is broken\n");
        close(file);
        return -2;
    }

    printf("Message: %s\n", readBuff);

    close(file);

    return 0;
}
#endif





