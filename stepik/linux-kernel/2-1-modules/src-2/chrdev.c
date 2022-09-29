#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

static dev_t first;
static unsigned int count = 1;
static int dev_major = 700;
static int dev_minor = 0;
static struct cdev* my_cdev;

#define MYDEV_NAME "My-char-dev"
#define KBUF_SIZE (size_t)((10) * PAGE_SIZE)


static int mychrdev_open(struct inode* inode, struct file* file)
{
	static int counter = 0;

	char* kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);

	file->private_data = kbuf;

	printk(KERN_INFO "Open %s\n", MYDEV_NAME);
	
	counter++;

	printk(KERN_INFO "counter: %d\n", counter);
	printk(KERN_INFO "module refcounter: %d\n", module_refcount(THIS_MODULE));

	return 0;
}

static int mychrdev_release(struct inode* inode, struct file* file)
{
	printk(KERN_INFO "Release %s\n", MYDEV_NAME);

	char* kbuf = file->private_data;

	printk(KERN_INFO "Free\n");

	if (kbuf)
	{
		kfree(kbuf);
	}
	kbuf = NULL;
	file->private_data = NULL;
	return 0;
}

static ssize_t mychrdev_read(struct file* file, char __user* buf, size_t lbuf, loff_t* pos)
{
	char* kbuf = file->private_data;

	int nbytes = lbuf - copy_to_user(buf, kbuf + *pos, lbuf);
	*pos += nbytes;

	printk(KERN_INFO "Read %s nbytes = %d pos = %d\n", MYDEV_NAME, nbytes, (int)*pos);

	return nbytes;
}	

static ssize_t mychrdev_write(struct file* file, const char __user* buf, size_t lbuf, loff_t* pos)
{
	char* kbuf = file->private_data;

	int nbytes = lbuf - copy_from_user(kbuf + *pos, buf, lbuf);
	*pos += nbytes;

	printk(KERN_INFO "Write %s nbytes = %d pos = %d\n", MYDEV_NAME, nbytes, (int)*pos);

	return nbytes;
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
	if (my_cdev)
	{
		cdev_del(my_cdev);
	}
	unregister_chrdev_region(first, count);

}

module_init(init_chrdev);
module_exit(cleanup_chrdev);
MODULE_LICENSE("GPL");

