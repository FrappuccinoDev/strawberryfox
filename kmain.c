#define KERNEL_VERSION "0x0-alpha"

#include "printk.h"

extern void kmain(void)
{
	fb_clear();
	printk("UwUabc");
	return;
}
