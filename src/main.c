#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/ioport.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Adam");
MODULE_DESCRIPTION("Libre Computer GPIO Driver");

#define CHAR_DEVICE_NAME "GPIO_dev"
#define DEVICE_COUNT 1
/* TODO, CHECK MEMORY BLOCK FOR DIGITAL GPIO */
#define GPIO_DIG_PHYSICAL_BASE_ADDRESS 0
#define GPIO_ANA_PHYSICAL_BASE_ADDRESS (0xc8100000 + 0x09 * sizeof(uint32_t))
#define GPIO_ANA_PHYSICAL_LENGTH ((0x0b - 0x09) * sizeof(uint32_t))

struct Context{
    dev_t number;
    struct cdev device;
    struct resource *reserved_analog_mapping;
    void *analog_gpio_mapping;
} static context;

static int open_callback(struct inode *inode, struct file *instance){
    pr_info("OPEN, CALLBACK GPIO driver\n");
    /* TODO, IMPLEMENT */
    return 0;
}

static int close_callback(struct inode *inode, struct file *instance){
    pr_info("CLOSE, CALLBACK GPIO driver\n");
    /* TODO, IMPLEMENT */
    return 0;
}

static ssize_t read_callback(struct file *instance, char __user *buffer, size_t size, loff_t *){
    pr_info("READ, CALLBACK GPIO driver\n");
    /* TODO, IMPLEMENT */
    return 0;   
}

static ssize_t write_callback(struct file *instance, const char __user *buffer, size_t size, loff_t *){
    pr_info("WRITE, CALLBACK GPIO driver\n");
    /* TODO, IMPLEMENT */
    return 0;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = open_callback,
    .release = close_callback,
    .read = read_callback,
    .write = write_callback
};

static int __init driver_main(void){
    int status = 0;
    pr_info("ENTER, GPIO driver\n");
    status = alloc_chrdev_region(&context.number, 0, DEVICE_COUNT, CHAR_DEVICE_NAME);
    if(status < 0){
        pr_err("COULD NOT REGISTER DEVICE NUMBER FOR: %s\n", CHAR_DEVICE_NAME);
        return status;
    }
    cdev_init(&context.device, &fops);
    context.device.owner = THIS_MODULE;
    /* NOTIFY KERNEL WE WILL BE USING THIS PHYSICAL ADDRESS SPACE */
    context.reserved_analog_mapping = request_mem_region(GPIO_ANA_PHYSICAL_BASE_ADDRESS, GPIO_ANA_PHYSICAL_LENGTH, "");
    /* MAP GPIO PHYSICAL ADDRESSES INTO KERNEL VIRTUAL MEMORY */
    context.analog_gpio_mapping = ioremap(GPIO_ANA_PHYSICAL_BASE_ADDRESS, GPIO_ANA_PHYSICAL_LENGTH);
    if(context.analog_gpio_mapping == NULL){
        pr_err("COULD NOT MEMORY MAP THE GPIO ADDRESS SPACE, OFF: %lx, LEN: %lu\n", GPIO_ANA_PHYSICAL_BASE_ADDRESS, GPIO_ANA_PHYSICAL_LENGTH);
        return -EADDRNOTAVAIL;
    }
    /* LAST THING TO DO, AFTER THIS POINT DEVICE CAN BE CALLED FROM USER-SPACE */
    cdev_add(&context.device, context.number, DEVICE_COUNT);
    pr_info("REGISTERED DRIVER: %s WITH MAJOR: %d\n", CHAR_DEVICE_NAME, MAJOR(context.number));
    return 0;
}

static void __exit driver_exit(void){
    /* REMOVE DEVICE FILE */
    cdev_del(&context.device);
    /* CLEAR GPIO MMAP */
    iounmap(context.analog_gpio_mapping);
    /* INFORM KERNEL WE ARE NO LONGER USING THE GPIO ADDRESS SPACE */
    release_mem_region(GPIO_ANA_PHYSICAL_BASE_ADDRESS, GPIO_ANA_PHYSICAL_LENGTH);
    unregister_chrdev_region(context.number, 1);
    pr_info("EXIT, GPIO driver\n");
}

module_init(driver_main);
module_exit(driver_exit);