#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#define led_num 5

MODULE_AUTHOR("Ryuichi Ueda & Gaku Kuwano");
MODULE_DESCRIPTION("driver for LED cotrol");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static int gpio[led_num] = {25, 8, 7, 12, 16};

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t*pos)
{
	char c;
	if(copy_from_user(&c, buf, sizeof(char)))
		return -EFAULT;

//	printk(KERN_INFO "receive %c\n", c);
	if(c=='0'){
		gpio_base[10] = 1 << gpio[0];	
		gpio_base[10] = 1 << gpio[1];	
		gpio_base[10] = 1 << gpio[2];	
		gpio_base[10] = 1 << gpio[3];	
		gpio_base[10] = 1 << gpio[4];	
	}
	else if (c == '1')
		gpio_base[7] = 1 << gpio[0];
	else if (c == '2')
		gpio_base[7] = 1 << gpio[1];
	else if (c == '3')
		gpio_base[7] = 1 << gpio[2];
	else if (c == '4')
		gpio_base[7] = 1 << gpio[3];
	else if (c == '5')
		gpio_base[7] = 1 << gpio[4];
	
	return 1;
}

static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t* pos)
{
	int size = 0;
	char sushi[] = {0xF0, 0x9F, 0x8D, 0xA3, 0x0A};
	if(copy_to_user (buf+size, (const char *)sushi, sizeof(sushi))){
		printk(KERN_ERR "sushi : copy_to_user faild\n");
	return -EFAULT;
	}
	size += sizeof(sushi);
	return size;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write
//	.read = sushi_read
};

static int __init init_mod(void)
{
	int retval, i;
	retval = alloc_chrdev_region(&dev, 0, 1, "myked");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed. \n");
		return retval;
	}
	printk(KERN_INFO "%s is loaded. major:%d\n", __FILE__, MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_sdd failed. major:%d, minor:%d\n", MAJOR(dev), MINOR(dev));
		return retval;
	}

	cls = class_create(THIS_MODULE, "myled");
	if(IS_ERR(cls)){	
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));
	
	gpio_base = ioremap_nocache(0xfe200000, 0xA0);

	for(i = 0; i < led_num; i++){
		const u32 led = gpio[i];
		const u32 index = led/10;
		const u32 shift = (led%10)*3;
		const u32 mask = ~(0x7 << shift);
		gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
	}
	return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n", __FILE__, MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);
