#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define BCM2711_PERI_BASE   0xfe000000
#define GPIO_BASE           (BCM2711_PERI_BASE + 0x200000) /* GPIO controller */

#define LED_PIN_26			7 /* physical pin 26; gpio 7 */

#define BLOCK_SIZE			(4 * 1024)

#define BLINK_TIMEOUT_US	200000	

int mem_fd;
void *gpio_map;
volatile unsigned *gpio;

/**/
static int init_io(void);

/* GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y) */
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  /* sets   bits which are 1 ignores bits which are 0 */
#define GPIO_CLR *(gpio+10) /* clears bits which are 1 ignores bits which are 0 */
 
int init_io(void)
{
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0)
	{
        printf("can't open /dev/mem \n");
        return(-1);
    }
	else
	{
        printf("/dev/mem opened\n");
        
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
        printf("/dev/mem closed\n");
        
        if (gpio_map == MAP_FAILED) 
		{
            printf("mmap error %d\n", (int)gpio_map);
            return(-1);
        }
		else
		{
            printf("mmap Success.\n");
        }
    }
    
	/* Always use volatile pointer! */
	gpio = (volatile unsigned *)gpio_map;

	return 0;
}

/**/
int main(void)
{    
    if(init_io() == -1) 
    {
        printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        return -1;
    }
    
    /* must use INP_GPIO before we can use OUT_GPIO */
	INP_GPIO(LED_PIN_26); 
    OUT_GPIO(LED_PIN_26);
    
    for (;;)
    {
        GPIO_CLR = 1 << LED_PIN_26;
#if 0
        printf("LED OFF\n");
#endif        
		usleep(BLINK_TIMEOUT_US);

        GPIO_SET = 1 << LED_PIN_26;
#if 0
        printf("LED ON\n");
#endif        
		usleep(BLINK_TIMEOUT_US);
    }
    
    printf("- finished -\n");
    return 0;
}
