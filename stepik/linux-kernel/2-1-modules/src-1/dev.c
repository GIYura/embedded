#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h> /* Функция put_user */

static int init_module(void);
static void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "mydev"
#define BUF_LEN 128

static int Major;
static int Device_Status = 0;
static char msg[BUF_LEN];
static char *msg_Ptr;

static struct file_operations fops = 
{
	.open = device_open,
	.release = device_release,
	.read = device_read,
	.write = device_write
};

int init_module(void)
{
	/* Пытаемся зарегистрировать устройство */
	Major = register_chrdev(0, DEVICE_NAME, &fops);
	if (Major < 0) 
	{
		printk(KERN_ALERT "register_chrdev() error %d\n", Major);
		return Major;
	}
	printk(KERN_NOTICE "Major number %d\n", Major);
	printk(KERN_NOTICE "Please create a dev file with\n");
	printk(KERN_NOTICE "'mknod /dev/mydev c %d 0'.\n", Major);
	return SUCCESS;
}

void cleanup_module(void)
{
	/* Удаляем устройство */
	int res = unregister_chrdev(Major, DEVICE_NAME);
	if (res < 0)
	{
		printk(KERN_ALERT "unregister_chrdev() error: %d\n", res);
	}
}

static int device_open(struct inode *inode, struct file *file)
{
	if (Device_Status)
		return -EBUSY;
	Device_Open++;
	sprintf(msg, "Hello\n");
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);
	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
	Device_Status--;
	module_put(THIS_MODULE);
	return SUCCESS;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	printk(KERN_ALERT "Unsupported operation: write()\n");
	return -EINVAL;
}

static ssize_t mydevice_read(struct file *filp, char *buffer, size_t length, loff_t * offset)
{
	int bytes_read = 0; /* Сколько байтов записано в буфер */
	if (*msg_Ptr == 0)
	/* Достигнут конец сообщения, возвращаем 0 как признак конца файла */
	return 0;
/* Самый важный момент: перемещение данных. Поскольку буфер
находится в сегменте данных пользовательского процесса
(в пространстве пользователя), а не в пространстве ядра,
то мы не можем выполнить простое присваивание. Чтобы
скопировать данные, нам нужно использовать функцию put_user(),
которая перенесет данные из пространства ядра в пространство пользователя
*/
	while (length && *msg_Ptr)
	{
		put_user(*(msg_Ptr++), buffer++);
		length--;
		bytes_read++;
	}
	/* Возвращаем количество реально записанных в буфер байтов */
	return bytes_read;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jura");
MODULE_DESCRIPTION("Driver for /dev/mydev");
MODULE_SUPPORTED_DEVICE("mydev");

