## Task Switching in ARM RL-RTX

Add two memory management RL-RTX primitives that has the ability to block and unblock a task. You may assume there is only one user-defined memory pool in the system. The memory pool is declared by <strong>_declare_box()</strong> and further initialized by <strong>_init_box()</strong>, which are existing RTX functions (in rt_MemBox.c).

Note you do not need to write your own memory management logic since the kernel has existing functions to manage fixed size memory pool. However the existing memory management logic does not have the ability to block or unblock a task. <strong>You will be concentrating on how to block/unblock a task when memory is unavailable/available.</strong>

The primitives to be added are described as follows.<br>
• <strong>void * os_mem_alloc (void *mem_pool)</strong>
  This function will try and return a fixed-size box of memory to the calling task from the memory pool pointed by mem_pool.     When there is not enough memory available, the calling task is blocked until enough memory becomes available. This function   will place tasks, which are waiting for memory, in the WAIT_MEM state, which is a newly introduced state. Tasks which are in   the WAIT_MEM will be blocked from running. <u>The tricky part</u>: when a memory box becomes available (i.e. another task     calls <strong>os_mem_free(mem_pool, box1))</strong>, the highest priority (and longest waiting) task, in WAIT_MEM state,       receives the same memory address as box1. You will be writing your solution for this primitive in rt_MemBox_ext.c in the       function <strong>rt_mem_alloc(void *mem_pool).</strong><br>
• <strong>OS_RESULT os_mem_free (void *mem_pool, void *box)</strong>
  This function frees the memory block (whose address is box) in memory pool mem_pool. Note the box is allocated by             os_mem_alloc from the memory pool of mem_pool. This function returns OS_R_OK on success and OS_R_NOK otherwise. If there are   tasks waiting for memory and memory becomes available, the highest priority waiting task will get the memory and then be       unblocked and switched to READY state. Preemption may happen if the unblocked task has higher priority than the task that     calls this function to free up the memory. <u>Tip: you only need to free box from the memory pool mem_pool if there are no     tasks waiting for memory (i.e. called <strong>os_mem_alloc()</strong> and got blocked). You will be writing your solution for this primitive in rt_MemBox_ext.c in the function <strong>rt_mem_free(void *mem_pool, void *box).</strong>

Create a set of testing tasks to demonstrate that you have successfully implemented the
required primitives. Your test tasks should do the following tests.<br>
• A task can allocate a memory box from a memory pool using <strong>os_mem_alloc().</strong><br>
• A task will get blocked if there is no memory available when <strong>os_mem_alloc()</strong> is called.<br>
• A blocked task (state=WAIT_MEM) will be resumed once enough memory is available in the system.<br>
• Create a testing scenario that multiple tasks with different priorities are all blocked waiting for memory. When memory becomes available, test whether it is the highest priority task that waits the longest that gets the memory first.
