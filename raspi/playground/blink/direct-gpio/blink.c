#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define BCM2711_PERI_BASE   0xfe000000
#define GPIO_BASE           (BCM2711_PERI_BASE + 0x200000) /* GPIO controller */

#define GPIO_LED			21

#define BLOCK_SIZE			(4 * 1024)

static volatile unsigned *gpio;

static int gpioInit(void);

/* GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y) */
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define GPIO_SET *(gpio+7)  /* sets   bits which are 1 ignores bits which are 0 */
#define GPIO_CLR *(gpio+10) /* clears bits which are 1 ignores bits which are 0 */
 
int gpioInit(void)
{
    int mem_fd;
    void *gpio_map;

    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0)
    {
        printf("can't open /dev/mem \n");
        return -1;
    }
    else
    {
        /* mmap GPIO */
        gpio_map = mmap(
            NULL,					/* Any adddress in our space will do */
            BLOCK_SIZE,				/* Map length */
            PROT_READ|PROT_WRITE,	/* Enable reading & writting to mapped memory */
            MAP_SHARED,       		/* Shared with other processes */
            mem_fd,           		/* File to map */
            GPIO_BASE         		/* Offset to GPIO peripheral */   
        );
        
        close(mem_fd);

        if (gpio_map == MAP_FAILED) 
        {
            printf("mmap error %d\n", (int)gpio_map);
            return -2;
        }
    }
    
    /* Always use volatile pointer! */
    gpio = (volatile unsigned *)gpio_map;
    printf ("%s\n", "Blinking...");
    return 0;
}

/**/
int main(int argc, char* argv[])
{
    unsigned int blinkTimeout = 0;
    
    if (argc != 2)
    {
        printf("Invalid number of arguments\n");
        return -1;
    }

    blinkTimeout = atoi(argv[1]) * 1000;

    if (blinkTimeout == 0)
    {
        printf("Invalid timeout\n");
        return -2;
    }
    
    if (gpioInit() == -1) 
    {
        printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        return -3;
    }
    
    /* must use INP_GPIO before we can use OUT_GPIO */
    INP_GPIO(GPIO_LED); 
    OUT_GPIO(GPIO_LED);
    
    for (;;)
    {
        GPIO_CLR = 1 << GPIO_LED;

        usleep(blinkTimeout);
        
        GPIO_SET = 1 << GPIO_LED;

        usleep(blinkTimeout);
    }
    
    printf("- finished -\n");
    return 0;
}
