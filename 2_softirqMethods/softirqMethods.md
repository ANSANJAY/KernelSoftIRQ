softirq methods
===================

Registering softirq handlers:
-------------------------

Software interrupts must be registered before the kernel can execute them.

open_softirq is used for associating the softirq instance with the corresponding bottom halve routine.

void open_softirq(int nr, void (*action)(struct softirq_action *))
{
        softirq_vec[nr].action = action;
}

It is being called for example from networking subsystem.

net/core/dev.c:
---------------
        open_softirq(NET_TX_SOFTIRQ, net_tx_action);
        open_softirq(NET_RX_SOFTIRQ, net_rx_action);

Execution of softirq:
----------------------

The kernel maintains a per-CPU bitmask indicating which softirqs need processing at any given time
irq_stat[smp_processor_id].__softirq_pending.

Drivers can signal the execution of soft irq handlers using a function raise_softirq().
This function takes the index of the softirq as argument.

void raise_softirq(unsigned int nr)
{
        unsigned long flags;

        local_irq_save(flags);
        raise_softirq_irqoff(nr);
        local_irq_restore(flags);
}


local_irq_save 		--> Disables interrupts on the current processor where code is running
raise_softirq_irqoff 	--> sets the corresponding bit in the local CPUs softirq bitmask to mark the specified softirq as pending
local_irq_restore	--> Enables the interrupts

raise_softirq_irqoff if executed in non-interrupt context, will invoke wakeup_softirqd(), to wake up, if necessary the ksoftirqd kernel thread of that local CPU

What is the benefit of per-CPU Bitmask?
========================================

By using a processors specific bitmap, the kernel ensures that several softIRQs — even identical ones — can be executed on different CPUs at the same time.

Executing Softirqs
=====================

The actual execution of softirqs is managed by do_softirq()

Implementation : kernel/softirq.c

do_softirq() will call __do_softirq(), if any bit in the local softirq bit mask is set.

__do_softirq() then iterates over the softirq bit mask (least signicant bit) and invokes scheduled softirq handlers.


