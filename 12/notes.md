Important Points related to softirqs
-------------------------------------

1. Compile Time:
	Declared at compile time in an enumerator
	Not suitable for linux kernel modules

2. Execution:
	Executed as early as possible
		After return of a top handler and before return to a system call
	This is achieved by giving a high priority to the executed softirq handlers

3. Parallel:
	Softirqs can run in parallel
	Each processor has its own softirq bitmap
	One softirq cannot be scheduled twice on the same processor
	One softirq may run in parallel on other

4. Priority:
	Kernel iterates over the softirq bitmap, least significant bit (LSB) first, and execute the associated
	softirq handlers
	
