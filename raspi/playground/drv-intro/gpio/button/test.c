#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>

int main(int argc, char* argv[])
{
    int f;
    struct pollfd poll_fds[1];
    int ret;
    char value[4];
    int n;

    f = open("/sys/class/gpio/gpio4", O_RDONLY);
    if (f < 0 )
    {
        printf("Can't open file\n");
        return 1;
    }
	
    poll_fds[0].fd = f;
    poll_fds[0].events = POLLPRI | POLLERR;

    while (1)
    {
        printf("Press the button ...\n");
		
        ret = poll(poll_fds, 1, -1);
        if (ret > 0)
        {
            n = read(f, &value, sizeof(value));
            printf("Button pressed: read %d bytes, value = %c\n", n, value[0]);
        }
    }

    return 0;
}

