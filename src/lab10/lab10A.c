/*
iptables sux. 
*/


#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

#include <linux/fs.h>        // included for filesystem structs
#include <linux/miscdevice.h>// included for device driver stuff :
#include <linux/string.h>    // Because memcpy :)
#include <linux/random.h>    // get_random_bytes()

// Networking Includes
#include <net/protocol.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>

#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Biernat");
MODULE_DESCRIPTION("MBE Lab 10A");


typedef struct disallow_filter {
    unsigned int pr_num;
    unsigned int port;
    unsigned int id;
    struct disallow_filter * next;
    struct disallow_filter * prev;
}d;

typedef struct callback_filter {
    unsigned int pr_num;
    unsigned int id;

    void (*callback)(struct callback_filter *);
    struct callback_filter * next;
    struct callback_filter * prev;
}c;

struct disallow_filter * dfilter_head;
struct callback_filter * cfilter_head;
struct nf_hook_ops nfho;

unsigned int pkt_hook(unsigned int hooknum, struct sk_buff *skb, const struct 
             net_device * in, const struct net_device * out, 
	                  int (*okfn)(struct sk_buff *)) {
/*
    This function filters packets as they come into the system.
    Callback filters take precedence over disallow filters.
*/
    
    struct disallow_filter * walkera;
    struct callback_filter * walkerb;
    struct iphdr * ip_header;
    
    printk(KERN_INFO "[uTables] Got a packet!\n");

    ip_header = (struct iphdr *)skb_network_header(skb);

    walkera = dfilter_head;
    walkerb = cfilter_head;
    
    while(walkerb != 0)  {
        if(walkerb->pr_num == ip_header->protocol) {
            break;
        }
        walkerb = walkerb->next;
    }
    if (walkerb) {
        walkerb->callback(walkerb);
        return NF_ACCEPT;
    }

    while(walkera != 0) {
        if (walkera->pr_num == ip_header->protocol) {
            break;
        }
        walkera = walkera->next;
    }
    if (walkera) {
        printk(KERN_INFO "[uTables] Caught a disallowed Packet!\n");
        return NF_DROP;
    }


    return NF_ACCEPT;
}

void emulate_packet(int pnum) {
    struct disallow_filter * walkera;
    struct callback_filter * walkerb;
    printk(KERN_INFO "[uTables] Emulating Protocol: %d\n", pnum);
    

    walkera = dfilter_head;
    walkerb = cfilter_head;
    
    while(walkerb != 0)  {
        if(walkerb->pr_num == pnum) {
            break;
        }
        walkerb = walkerb->next;
    }
    if (walkerb) {
        printk(KERN_INFO "Found callback filter!\n");
        walkerb->callback(walkerb);
        return;
    }

    while(walkera != 0) {
        if (walkera->pr_num == pnum) {
            break;
        }
        walkera = walkera->next;
    }
    if (walkera) {
        printk(KERN_INFO "[uTables] Caught a disallowed Packet!\n");
        return;
    }
    return;
}

void default_callback(struct sk_buff  * skb) {
    printk(KERN_INFO "[uTables] Default Callback Hit!\n");
    return;
}

static ssize_t pwn_read(struct file* file, char * buf, size_t count, loff_t *ppos)
{
    return count;
}

int add_cfilter(struct callback_filter * filt) {
/*
    Add a callback filter to uTables.
*/
    struct callback_filter * nfilter, *walker;
    printk("[uTables] Adding a callback filter\n");
    
    nfilter = kmalloc(sizeof(struct callback_filter), GFP_KERNEL);
    nfilter->pr_num = filt->pr_num;
    nfilter->id = filt->id;
    nfilter->callback = default_callback;
    nfilter->next = 0;

    walker = cfilter_head;
    while(walker->next != 0) {
        walker = walker->next;
    }
    walker->next = nfilter;
    nfilter->prev = walker;
    
    printk(KERN_INFO "New Filter At Address: %p\n", nfilter);
    printk(KERN_INFO "New Filter Protocol: %u\n", nfilter->pr_num);
    printk(KERN_INFO "New Filter ID: %u\n", nfilter->id);
    printk(KERN_INFO "New Filter Callback @: %p\n", nfilter->callback);
    printk(KERN_INFO "New Filter NEXT: %p\n", nfilter->next);
    printk(KERN_INFO "New Filter PREV: %p\n", nfilter->prev);

    return 0;

}

int add_dfilter(struct disallow_filter * filt) {
/*
    Add a disallow filter to uTables.
*/

    struct disallow_filter * nfilter, *walker;
    
    printk("PR NUM: %d\n", filt->pr_num);
    nfilter = kmalloc(sizeof(struct disallow_filter), GFP_KERNEL);
    nfilter->pr_num = filt->pr_num;    
    nfilter->port = filt->port;
    nfilter->id = filt->id;
    nfilter->next = 0;

    walker = dfilter_head;
    while(walker->next != 0) {
        walker = walker->next;
    }
    walker->next = nfilter;
    nfilter->prev = walker;
    
    printk(KERN_INFO "New Filter At Address: %p", nfilter);
    printk(KERN_INFO "New Filter Protocol: %u\n", nfilter->pr_num);
    printk(KERN_INFO "New Filter Port: %u\n", nfilter->port);
    printk(KERN_INFO "New Filter ID: %u\n", nfilter->id);

    return 0;
}

int remove_defilter(int pr_num) {
/*
     Remove a filter for the specified protocol number. 
*/
     struct disallow_filter * walker;

     walker = dfilter_head;
     while(walker->pr_num != pr_num && walker != NULL){
         walker = walker->next;
     }
     if(walker) {
         printk(KERN_INFO "Removing Filter for %u at %08x\n", walker->pr_num, walker);
         walker->prev->next = walker->next;
	 if(walker->next) {
	     walker->next->prev = walker->prev;
         }
         kfree(walker);
         return 0;
     }
    return -1;
}

int modify_callback(void * data) {
/*
    Apart from the default Callback, you may load
    additional kernel modules and use their functions
    as callback routines from the filtering hook here.
*/
    struct callback_filter * walker;
    unsigned int addr;
    unsigned int cid;

    memcpy(&cid, data, 4);
    memcpy(&addr, data + 4, 4);
    printk(KERN_INFO "Addr: %u\n", addr);
    printk(KERN_INFO "ID: %u\n", cid);
    
    if (addr < 0xc0000000) {
        printk(KERN_INFO "[ERROR] Userspace Address detected!\n");
        return -1;
    }

    walker = cfilter_head;
    while (walker != 0) {
        if (walker->id == cid) {
            break;
        }
        walker = walker->next;
    }
    if (walker) {
        walker->callback = addr;
        printk(KERN_INFO "Updated Filter ID: %u Callback to : %u\n",walker->id, walker->callback);
    }
    else {
        printk(KERN_INFO "Could not find Filter with ID: %u\n",walker->id);
        return -1;
    }
    return 0;
}

static ssize_t pwn_write(struct file* file, const char * buf, size_t count, loff_t *ppos)
{ // This is how you configure uTables
   
    if (buf[0] == '\x01') { // Now you know you're talking to this thing :)
        printk(KERN_INFO "The flag is in /root/flag\n");
    }

    if (buf[0] == '\x02') { // Add a disallow filter
        printk(KERN_INFO "[uTables] Adding new disallow filter\n");
        printk(KERN_INFO "PR: %u", buf[1]);
        add_dfilter( (struct disallow_filter *) &(buf[1]));
    }

    if (buf[0] == '\x03') { // Add a callback filter
        printk(KERN_INFO "[uTables] Adding a new callback filter\n");
        add_cfilter( (struct callback_filter *) &(buf[1]));
    }

    if (buf[0] == '\x04') { // Modify a callback function
        printk(KERN_INFO "[uTables] Modifying a callback\n");
        modify_callback((void *) &(buf[4]));
    }

    if (buf[0] == '\x05') { // Emulate a Packet arriving in the kernel.
        printk(KERN_INFO "[uTables] Emulating a packet arriving\n");
        emulate_packet( (int) (buf[1]));

    }

    return count;
}


static const struct file_operations pwnops = {
    .owner  = THIS_MODULE,
    .read   = pwn_read,
    .write  = pwn_write,
};

static struct miscdevice pwn_dev = {
    MISC_DYNAMIC_MINOR, "pwn" , &pwnops
};

static int __init mod_init(void)
{
/*
    Initialize data structures and register a device that will be used to 
    configure uTables.
    Also set up our networking hook so we can look at packets coming into the
    kernel.
*/

    int ret;
    // Register our device and create heads for our linked lists 
    ret = misc_register(&pwn_dev); 
    dfilter_head = kmalloc(sizeof(struct disallow_filter), GFP_KERNEL);
    cfilter_head = kmalloc(sizeof(struct callback_filter), GFP_KERNEL);
   
    // Initialize our linked list heads
    dfilter_head->pr_num = -1;
    dfilter_head->port = -1;
    dfilter_head->next = 0;
    dfilter_head->prev = 0;

    cfilter_head->pr_num = -1;
    cfilter_head->id = -1;
    cfilter_head->callback = default_callback;
    cfilter_head->next = 0;
    cfilter_head->prev = 0;

    // Set up our basic netfilter hook
    nfho.hook = pkt_hook;
    nfho.hooknum = 0;
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;

    // Register our hook 
    nf_register_hook(&nfho);

    printk(KERN_INFO "Finished Init\n"); 
    printk(KERN_INFO "Can u get r00t?\n");
    return 0;    
}

static void __exit mod_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
    misc_deregister(&pwn_dev);
    nf_unregister_hook(&nfho);
}


// We're "registering" our module with the rest of the Kernel here.
module_init(mod_init);
module_exit(mod_cleanup);


