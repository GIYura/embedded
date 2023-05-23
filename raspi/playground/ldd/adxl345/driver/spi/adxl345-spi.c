#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/spi/spi.h>
#include <linux/kernel.h>

#define DRIVER_NAME     "adxl345-spi"
#define DRIVER_CLASS    "adxl345Class-spi"

#define ADXL_ID_ADDR    0x00

#define SPI_BUS_NUM     0

#if 1
/* Register information about your slave device */
struct spi_board_info adxl_spi_board_info = 
{
  .modalias     = "adxl345-spi-driver",
  .max_speed_hz = 5000000,              // speed your device (slave) can handle
  .bus_num      = SPI_BUS_NUM,          // SPI 0
  .chip_select  = 0,                    // /*TODO  */Use 0 Chip select (GPIO 18)
  .mode         = SPI_MODE_3            // SPI mode 3
};

static struct spi_master* master = NULL;

static struct spi_device* adxl_spi_device;
static struct device adxl_device;
#endif

static struct spi_driver adxl_spi_driver = {
    .driver = {
        .name = DRIVER_NAME,
        .owner = THIS_MODULE,
    },
};


/* Meta Information */
MODULE_AUTHOR("Jura");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A driver for reading out ID ADXL345 Accelerometer");

/* Variables for Device and Deviceclass*/
static dev_t deviceNumber;
static struct class* devClass;
static struct cdev device;

#if 0
static u8 readId(void)
{
    u8 id = spi_w8r8(adxl345_spi_device, ADXL_ID_ADDR);
    return id;
}
#endif

#if 0
/**/
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs)
{
    int to_copy, not_copied, delta;

    /* Get amount of data to copy */
    to_copy = min(count, (sizeof(adxl345Buffer) - 1));

    /* Copy data to user */
    not_copied = copy_from_user(adxl345Buffer, user_buffer, to_copy);

    /* Calculate data */
    delta = to_copy - not_copied;

    return delta; 
}
#endif

/**
 * @brief Get data out of buffer
 */
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs)
{
    int to_copy, not_copied, delta;
    u8 outBuff[20];
#if 0
    /* Get amount of bytes to copy */
    to_copy = min(sizeof(outBuff), count);

    /* read ID */
    outBuff[0] = readId();

    /* Copy Data to user */
    not_copied = copy_to_user(user_buffer, outBuff, to_copy);

    /* Calculate delta */
    delta = to_copy - not_copied;
#endif
    return delta;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *deviceFile, struct file *instance)
{
    printk("ADXL345 DeviceDriver -  Open was called\n");
    return 0;
}

/**
 * @brief This function is called, when the device file is close
 */
static int driver_close(struct inode *deviceFile, struct file *instance)
{
    printk("ADXL345 DeviceDriver -  Close was called\n");
    return 0;
}

/* Map the file operations */
static struct file_operations devOps = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
#if 0
    .read = driver_read,
#endif
#if 0
    .write = driver_write,
#endif
};

/**
 * @brief function, which is called after loading module to kernel, do initialization there
 */
static int __init ModuleInit(void)
{
    int ret = 0;
    printk("ADXL345 DeviceDriver - Hello Kernel\n");

    /* Allocate Device Nr */
    if (alloc_chrdev_region(&deviceNumber, 0, 1, DRIVER_NAME) < 0)
    {
        printk("ADXL345 Device Number could not be allocated!\n");
        return ret;
    }
    printk("ADXL345 DeviceDriver - Device Number %d was registered\n", deviceNumber);

    /* Create Device Class */
    if ((devClass = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL)
    {
        printk("ADXL345 Device Class can not be created!\n");
        goto ClassError;
    }

    /* Create Device file */
    if (device_create(devClass, NULL, deviceNumber, NULL, DRIVER_NAME) == NULL)
    {
        printk("ADXL345 Can not create device file!\n");
        goto FileError;
    }

    /* Initialize Device file */
    cdev_init(&device, &devOps);

    /* register device to kernel */
    if (cdev_add(&device, deviceNumber, 1) == -1)
    {
        printk("ADXL345 Registering of device to kernel failed!\n");
        goto AddError;
    }

#if 1
/* TODO: */
 /*
    1. alloc master
    2. register master
    3. new device
    4. register driver
    5. spi setup
  */
    /*1*/
    master = spi_alloc_master(&adxl_device, 0);
    if (master == NULL)
    {
        printk("Error alloc master\n");
        return -1;
    }
    /* TODO:
    master->bus_num = ;
     */

    /*
    ret = spi_register_master(master);
    if (ret < 0)
    {
        spi_master_put(master);
    }
    */
    
    /* create a new slave device, given the master and device info */
    adxl_spi_device = spi_new_device(master, &adxl_spi_board_info);
    if (adxl_spi_device == NULL) 
    {
        printk("FAILED to create slave.\n");
        return -1;
    }

    /* 8-bits in a word */
    adxl_spi_device->bits_per_word = 8;

    /* setup the SPI slave device */
    ret = spi_setup(adxl_spi_device);
    if (ret < 0)
    {
        printk("FAILED to setup slave.\n");
        spi_unregister_device(adxl_spi_device);
        return -1;
    }
    

    printk("ADXL345 Driver added!\n");
#endif

    return ret;

AddError:
    device_destroy(devClass, deviceNumber);
FileError:
    class_destroy(devClass);
ClassError:
    unregister_chrdev(deviceNumber, DRIVER_NAME); 
    return -1;
}

/**
 * @brief function, which is called when removing module from kernel
 * free alocated resources
 */
static void __exit ModuleExit(void)
{
    printk("ADXL345 DeviceDriver - Goodbye, Kernel!\n");

    spi_unregister_master(master);
    cdev_del(&device);
    device_destroy(devClass, deviceNumber);
    class_destroy(devClass);
    unregister_chrdev_region(deviceNumber, 1);
}

module_init(ModuleInit);
module_exit(ModuleExit);

