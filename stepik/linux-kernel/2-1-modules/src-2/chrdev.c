#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

static char* kbuf;
static dev_t first;
static unsigned int count = 1;
static int dev_major = 700;
static int dev_minor = 0;
static struct cdev* my_cdev;

#define MYDEV_NAME "My-char-dev"
#define KBUF_SIZE (size_t)((10) * PAGE_SIZE)


static int mychrdev_open(struct inode* inode, struct file* file)
{
	printk(KERN_INFO "Open %s\n", MYDEV_NAME);
	return 0;
}

static int mychrdev_release(struct inode* inode, struct file* file)
{
	printk(KERN_INFO "Release %s\n", MYDEV_NAME);
	return 0;
}

static ssize_t mychrdev_read(struct file* file, char __user* buf, size_t lbuf, loff_t* pos)
{
	printk(KERN_INFO "Read %s\n", MYDEV_NAME);
	return 0;
}	

static ssize_t mychrdev_write(struct file* file, const char __user* buf, size_t lbuf, loff_t* pos)
{
	printk(KERN_INFO "Write %s\n", MYDEV_NAME);
	return 0;
}

static const struct file_operations mycdev_fops = 
{
	.owner = THIS_MODULE,
	.read = mychrdev_read,
	.write = mychrdev_write,
	.open = mychrdev_open,
	.release = mychrdev_release,
};

static int __init init_chrdev(void)
{
	printk(KERN_INFO "Hello Kernel\n");

	kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);

	first = MKDEV(dev_major, dev_minor);
	register_chrdev_region(first, count, MYDEV_NAME);

	my_cdev = cdev_alloc();

	cdev_init(my_cdev, &mycdev_fops);
	cdev_add(my_cdev, first, count);


	return 0;
}

static void __exit cleanup_chrdev(void)
{
	printk(KERN_INFO "Module removed\n");
}

module_init(init_chrdev);
module_exit(cleanup_chrdev);
MODULE_LICENSE("GPL");

