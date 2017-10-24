#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>          
#include <linux/errno.h>       
#include <linux/types.h>       
#include <linux/fcntl.h>       
#define   CALL_DEV_NAME            "calldev"
#define   CALL_DEV_MAJOR            240      

int call_open (struct inode *inode, struct file *filp) {
	int num = MINOR(inode->i_rdev); 
	
	printk( "call open -> minor : %d\n", num );
	
	return 0;
}

ssize_t call_read(struct file *filp, char *buf, size_t count, loff_t *f_pos) {
	printk( "call read -> buf : %08X, count : %08X \n", buf, count );
	
	return 0x33;
}

ssize_t call_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos) {
	printk( "call write -> buf : %08X, count : %08X \n", buf, count );
	
	return 0x43;
}

struct file_operations call_fops =
{  .owner    = THIS_MODULE,
	.read     = call_read,     
	.write    = call_write,    
	.open     = call_open,     
};

int call_init(void) {
	int result;
	
	printk( "call call_init \n" );    
	
	result = register_chrdev( CALL_DEV_MAJOR, CALL_DEV_NAME, &call_fops);
	
	if (result < 0) return result;

	return 0;
}

void call_exit(void) {
	printk( "call call_exit \n" );    
	
	unregister_chrdev( CALL_DEV_MAJOR, CALL_DEV_NAME );
}

module_init(call_init);
module_exit(call_exit);
MODULE_LICENSE("Dual BSD/GPL");
