
#include <linux/kernel.h>

 asmlinkage long sys_hello(void)
{
        printk("Greeting from kernel and team no %d\n",22);
        return 0;
 }
