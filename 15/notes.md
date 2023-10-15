When are pending softirqs run?
-------------------------------

Pending softirq handlers are checked and executed at various points in the kernel code.

	a) After the completion of hard interrupt handlers with IRQ Lines Enabled
		do_IRQ() function finishes handling an I/O interrupt and invokes the irq_exit()

	b) call to functions like local_bh_enable() or spin_unlock_bh()

	c) when one of the special ksoftirqd/n kernel threads is awakened
