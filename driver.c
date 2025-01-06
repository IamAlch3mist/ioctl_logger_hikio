#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/device.h>

#define DEVICE_NAME "hikio"

static dev_t dev_number;
static struct cdev simple_cdev;
static struct class *simple_class = NULL;

static long hikio_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
   int arry[4];
   arry[0]= 'A';
   arry[1]= 'B';
   arry[2]= 'C';
   arry[3]= 'D';

   struct hwif_getsecinfo {
   unsigned int magic;
   char buffer[252];
   };

   struct hwif_getsecinfo retbuf;

   retbuf.magic = 1212897107;

   printk(KERN_INFO "IOCTL: received cmd: 0x%x\n", cmd);

switch(cmd){
/* To Do:
 Add more cases to handle ioctl calls
*/

case 2147772418:
   copy_to_user((int*) arg, &arry, sizeof(arry));
   return 0;

case 2147772417:
   copy_to_user((struct hwif_getsecinfo*) arg, &retbuf, sizeof(retbuf));
   return 0;

}
return 0;
}


static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = hikio_ioctl,
};


static int __init init_hikio(void)
{
   printk(KERN_INFO "Tainted driver loading...\n");
//   int ret;
   alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);

//   printk(KERN_INFO "ret %d\n", ret);
   simple_class = class_create(THIS_MODULE, DEVICE_NAME);
   cdev_init(&simple_cdev, &fops);
   simple_cdev.owner = THIS_MODULE;
   cdev_add(&simple_cdev, dev_number, 1);
   device_create(simple_class, NULL, dev_number, NULL, DEVICE_NAME);
   printk(KERN_INFO "Tainted driver loaded successfully :) ");
   return 0;
}

static void exit_hikio(void) {
  device_destroy(simple_class, dev_number);
  cdev_del(&simple_cdev);
  class_destroy(simple_class);
  unregister_chrdev_region(dev_number, 1);
  printk(KERN_INFO "module removed \n");

}

module_init(init_hikio)
module_exit(exit_hikio)
MODULE_VERSION("1.1");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("IamAlch3mist");
