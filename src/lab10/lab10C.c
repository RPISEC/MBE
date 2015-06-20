/*
Unix-Dude sux at writing rootkits.

He forgot the get_r00t code q_q.
*/


#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

#include <linux/fs.h>        // included for filesystem structs
#include <linux/miscdevice.h>// included for device driver stuff :
#include <linux/string.h>    // Because memcpy :)
#include <linux/random.h>    // get_random_bytes()

#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Biernat");
MODULE_DESCRIPTION("MBE Lab 10 C");

unsigned int secret;

typedef struct key_material {
    char key[1024];
    void (*algo)(char *);
    int auth;
}da_keyz;


struct key_material * sekret;

static ssize_t pwn_write(struct file* file, const char * buf, size_t count, loff_t *ppos)
{ // Here we check for the password

    printk(KERN_INFO "%s\n",buf);
    if( count == 0x31337) {
        if (sekret->auth) {
	     // Do the root thing here.
	     printk(KERN_INFO "Nice privs bro.\n");
        }
	return 0x31337;
    }
    
    if(buf[0] == '\x01') {
        printk("Flag is @ /root/flag");
    }

    if ( ( *(unsigned int *)buf ^ 0xcafebabe) == 0) {
        printk(KERN_INFO "Performing Key Authentication now...\n");
	sekret->algo(buf);
    }

    return count;
}


static const struct file_operations pwnops = {
    .owner  = THIS_MODULE,
    .write  = pwn_write,
};

static struct miscdevice pwn_dev = {
    MISC_DYNAMIC_MINOR, "pwn" , &pwnops
};

void algo_xor(char * buf) {
/*
    Secure One-Time Pad Authentication Function.
*/
    int i;
    int sum;

    sum = 0;
    printk(KERN_INFO "Inside algo_xor!\n");
   
    for(i=0; i <= 1024; i++) {
        sekret->key[i] ^= buf[i];
    }
   
   for(i=0; i <= 1024; i++) {
        sum += sekret->key[i];
    }
    
    if(sum == 0) {
        sekret->auth = 1;
    }
    else {
        printk(KERN_INFO "Authentication Failed!\n");
    	memset(sekret, 0 , sizeof(struct key_material));
    	get_random_bytes(&(sekret->key),1024);
    }
    return;
}

//Think of this as the familiar "main" function
static int __init mod_init(void)
{
    int ret;
    // Register Device to /dev
    ret = misc_register(&pwn_dev);
    
    // Allocate Space for the key 
    sekret = kmalloc(sizeof(struct key_material), GFP_KERNEL);
    get_random_bytes(&sekret->key, 1024);
   
    // Set the algorithm to a sane default
    sekret->algo = algo_xor;   

    printk(KERN_INFO "Finished Init\n"); 
    printk(KERN_INFO "Can u get r00t?\n");
    return 0;    
}

static void __exit mod_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
    misc_deregister(&pwn_dev);
}


//We're "registering" our module with the rest of the Kernel here.
module_init(mod_init);
module_exit(mod_cleanup);


