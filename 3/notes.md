Creating a new softirq
-----------------------

You declare softirqs statically at compile time via an enum in <linux/interrupt.h>.

Creating a new softirq includes adding a new entry to this enum.

The index is used by the kernel as priority.

Softirqs with the lowest numerical priority execute before those with a higher numerical priority

Insert the new entry depending on the priority you want to give it.

Registering your handler
------------------------

Soft irq is registered at runtime via open_softirq().

It takes two parameters:

	a) Index
	b) Handler Function.

Raising your softirq
---------------------

To mark it pending, so it is run at the next invocation of do_softirq(), call raise_softirq()

Softirqs are most often raised from within interrupt handlers.



Other Details
-----------------
The softirq handlers run with interrupts enabled and cannot sleep.

While a handler runs, softirqs on the current processor are disabled.

Another processor, can however execute another softirq.

If the same softirq is raised again while it is executing, another processor can run in it simultaneously.

This means that any shared data even global data used only within the soft irq handler needs proper locking.

most softirq handlers resort to per-processor data (data unique to each processor and thus not requiring locking) and other tricks to avoid explicit locking and provide excellent scalability.
