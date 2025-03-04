#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE2(my_suma, int, a, int, b) {
    printk(KERN_INFO "Syscall suma: sumando %d y %d\n", a, b);
    return a + b;
}