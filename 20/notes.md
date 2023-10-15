Locking Between User Context and Softirqs
==========================================

spin_lock_bh()	Disables softirqs on the CPU and then grabs the lock

spin_unlock_bh() Release lock and enable softirqs


