Disabling/Enabling Softirqs
==============================

If a softirq shares data with user context, you have two problems.

1) the current user context can be interrupted by a softirq

2) the critical region could be entered from another CPU

Solution to  first problem
---------------------------

void local_bh_disable() 	Disable softirq and tasklet processing on the local processor

void local_bh_enable()		Enable softirq and tasklet processing on the local processor

The calls can be nested only the final call to local_bh_enable() actually enables bottom halves.
