#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Ryuichi Ueda and Kenta Akiyama");
MODULE_DESCRIPTION("driver for Roulette");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0.0");

const u32 pin[6] = {21, 20, 16, 12, 26, 19}; //21,20,16,12,26はLED 19はスピーカー
char pi[21] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6};
static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

int n = 50; //乱数

static ssize_t led_write(struct file* flip, const char* buf, size_t count, loff_t* pos){

	char c;
	int j;
	int k;
	int l = 1;
	int x = 0;

	if(copy_from_user(&c, buf, sizeof(char)))
	return -EFAULT;


	if(c == "0"){
		for(j = 0; j < n; j++){

			gpio_base[7] = 1 << pin[x];
			for(k = 0; k < 100 + 3*j; k++){
				gpio_base[7] = 1 << 19;
				udelay(1);
				gpio_base[10] = 1 << 19;
				udelay(1);
			}
			mdelay(50 + 5*j);
			gpio_base[10] = 1 << pin[x];
			x++;
			if(x == 5){
				x = 0;
		}
	
	}
	gpio_base[7] = 1 << pin[x];
	for(k = 0; k < 500000; k++){
		gpio_base[7] = 1 << 19;
		udelay(1);
		gpio_base[10] = 1 << 19;
		udelay(1);
	}
}

	else if (c == '1'){
		for(j = 0; j <=5; j++){
			gpio_base[10] = 1 << pin[j];
			}
		if( n > 60){
		n = n - pi[l];
		l++;
		}
		else if(n <= 60){
		n = n + pi[l];
		l++;
		}
	}
	if(j == 21){
		j = 1;
}
	return 1;
}


static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
};

static int __init init_mod(void)
{
	int i;
	int N = 6; //LEDとスピーカーの数
	int retval;

	retval = alloc_chrdev_region(&dev, 0, 1, "mydev");
	if(retval < 0){
	printk(KERN_ERR "alloc_chrdev_region failed.\n");
	return retval;
}

	printk(KERN_INFO "%s is loaded, major:%d\n",__FILE__, MAJOR(dev));
	
	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
		return retval;
	}
	cls = class_create(THIS_MODULE, "mydev");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}

	device_create(cls, NULL, dev, NULL, "mydev%d", MINOR(dev));

	gpio_base = ioremap_nocache(0xfe200000, 0xA0);

	for(i = 0; i < N; i++){
	const u32 index = pin[i]/10;
	const u32 shift = (pin[i]%10)*3;
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
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__, MAJOR(dev));
}
module_init(init_mod);
module_exit(cleanup_mod);
