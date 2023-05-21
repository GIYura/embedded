#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/spi/spi.h>
#include <linux/kernel.h>

#define DRIVER_NAME     "adxl345"
#define DRIVER_CLASS    "adxl345Class"

#define ADXL_ID_ADDR    0x00

#if 0
/* adapter = master */
static struct i2c_adapter* adxl345_i2c_adapter = NULL;   // I2C Adapter Structure

/* client = slave */
static struct i2c_client* adxl345_i2c_client = NULL;     // I2C Cient Structure
#endif

#define SPI_BUS_NUM     0

static struct spi_device* adxl345_spi_device;

/* Register information about your slave device */
struct spi_board_info  adxl345_spi_device_info = 
{
  .modalias     = "adxl345-spi-driver",
  .max_speed_hz = 4000000,              // speed your device (slave) can handle
  .bus_num      = SPI_BUS_NUM,          // SPI 0
  .chip_select  = 0,                    // /*TODO  */Use 0 Chip select (GPIO 18)
  .mode         = SPI_MODE_0            // SPI mode 0
};

static struct spi_master* master;

/* Meta Information */
MODULE_AUTHOR("Jura");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A driver for reading out ID ADXL345 Accelerometer");

#if 0
/* Defines for device identification */ 
#define I2C_BUS_AVAILABLE		1           /* The I2C Bus available on the raspberry */
#define SLAVE_DEVICE_NAME		"ADXL345"   /* Device and Driver Name */
#define ADXL345_SLAVE_ADDRESS	0x53        /* ADXL345 I2C address */

/* драйвер устройства на шине 
I2C driver Structure that has to be added to linux
*/
static struct i2c_driver adxl345_driver = {
    .driver = {
        .name = SLAVE_DEVICE_NAME,
        .owner = THIS_MODULE
    }
};

/* I2C Board Info strucutre */
static struct i2c_board_info adxl345_i2c_board_info = {
    I2C_BOARD_INFO(SLAVE_DEVICE_NAME, ADXL345_SLAVE_ADDRESS)
};
#endif

/* Variables for Device and Deviceclass*/
static dev_t deviceNumber;
static struct class* devClass;
static struct cdev device;

//static char adxl345Buffer[20];

static u8 readId(void)
{
    u8 id = spi_w8r8(adxl345_spi_device, ADXL_ID_ADDR);
    return id;
}

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

    /* Get amount of bytes to copy */
    to_copy = min(sizeof(outBuff), count);

    /* read ID */
    outBuff[0] = readId();

    /* Copy Data to user */
    not_copied = copy_to_user(user_buffer, outBuff, to_copy);

    /* Calculate delta */
    delta = to_copy - not_copied;

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
    .read = driver_read,
#if 0
    .write = driver_write,
#endif
};

/**
 * @brief function, which is called after loading module to kernel, do initialization there
 */
static int __init ModuleInit(void)
{
    int ret = -1;
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

/* TODO: */
#if 1
    master = spi_busnum_to_master(adxl345_spi_device_info.bus_num);
    if ( master == NULL )
    {
        printk("SPI Master not found.\n");
        return -1;
    }
#endif   

    // create a new slave device, given the master and device info
    adxl345_spi_device = spi_new_device(master, &adxl345_spi_device_info);
    if ( adxl345_spi_device == NULL ) 
    {
        printk("FAILED to create slave.\n");
        return -1;
    }
  
    // 8-bits in a word
    adxl345_spi_device->bits_per_word = 8;

    // setup the SPI slave device
    ret = spi_setup( adxl345_spi_device );
    if ( ret )
    {
        pr_err("FAILED to setup slave.\n");
        spi_unregister_device( adxl345_spi_device );
        return -1;
    }

#if 0
    /* Get I2C controller
    доступен ли на шине 1 i2c контроллер
    */
    adxl345_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);

    if (adxl345_i2c_adapter != NULL)
    {
        /* The interface is used to instantiate an I2C client device */
        adxl345_i2c_client = i2c_new_client_device(adxl345_i2c_adapter, &adxl345_i2c_board_info);
        if (adxl345_i2c_client != NULL)
        {
            /* add driver to subsystem */
            if (i2c_add_driver(&adxl345_driver) != -1)
            {
                ret = 0;
            }
            else
            {
                printk("ADXL345 Can't add driver...\n");
            }
        }
        /* must call i2c_put_adapter() when done with returned i2c_adapter device */
        i2c_put_adapter(adxl345_i2c_adapter);
    }
#endif

    printk("ADXL345 Driver added!\n");

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

    spi_unregister_device(adxl345_spi_device);
    cdev_del(&device);
    device_destroy(devClass, deviceNumber);
    class_destroy(devClass);
    unregister_chrdev_region(deviceNumber, 1);
}

module_init(ModuleInit);
module_exit(ModuleExit);

