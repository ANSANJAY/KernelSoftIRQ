#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/kthread.h>


MODULE_LICENSE("GPL");


static int test_hello_init(void)
{
	pr_info("%s: In init\n", __func__);
	pr_info("Disabling bottom halves\n");
	local_bh_disable();
	mdelay(10000);
	pr_info("Enabling bottom halves\n");
	local_bh_enable();

	return 0;

}

static void test_hello_exit(void)
{
	pr_info("%s: In exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
		
