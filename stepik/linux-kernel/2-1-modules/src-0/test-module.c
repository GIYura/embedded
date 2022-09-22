#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init ModuleInit(void)
{
	printk(KERN_INFO "Hello Kernel\n");
	return 0;
}

static void __exit ModuleExit(void)
{
	printk(KERN_INFO "Module removed\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jura");
MODULE_DESCRIPTION("Driver for /dev/mydev"); 
MODULE_SUPPORTED_DEVICE("mydev");

