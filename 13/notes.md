ksoftirqd
============

Softirqs are executed as long as the processor-local softirq bitmap is set.

Since softirqs are bottom halves and thus remain interruptible during execution, 

the system can find itself in a state where it does nothing else than 
	serving interrupts and 
	softirqs

incoming interrupts may schedule softirqs what leads to another iteration over the bitmap.

Such processor-time monopolization by softirqs is acceptable under high workloads (e.g., high IO or network traffic), but it is generally undesirable for a longer period of time since (user) processes cannot be executed.

Solution to above problem by kernel
======================================

After the tenth iteration(MAX_SOFTIRQ_RESTART) over the softirq bitmap, the kernel schedules the so-called ksoftirqd kernel thread, which takes control over the execution of softirqs.

Each processor has its own kernel thread called ksoftirqd/n, where n is the number of the processor

This processor-local kernel thread then executes softirqs as long as any bit in the softirq bitmap is set.

The aforementioned processor-monopolization is thus avoided by deferring softirq execution into process context (i.e., kernel thread), so that the ksoftirqd can be preempted by any other (user) process.

 ps -ef | grep ksoftirqd/

The spawn_ksoftirqd function starts these threads.

It is called early in the boot process.

static __init int spawn_ksoftirqd(void)
{
        cpuhp_setup_state_nocalls(CPUHP_SOFTIRQ_DEAD, "softirq:dead", NULL,
                                  takeover_tasklets);
        BUG_ON(smpboot_register_percpu_thread(&softirq_threads));

        return 0;
}
early_initcall(spawn_ksoftirqd);

File: kernel/softirq.c

Each ksoftirqd/n kernel thread runs the run_ksoftirqd()

static void run_ksoftirqd(unsigned int cpu)
{
        local_irq_disable();
        if (local_softirq_pending()) {
                /*
                 * We can safely run softirq on inline stack, as we are not deep
                 * in the task stack here.
                 */
                __do_softirq();
                local_irq_enable();
                cond_resched();
                return;
        }
        local_irq_enable();
}


