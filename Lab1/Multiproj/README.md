## Introduction to ARM RL-RTX Application and Kernel Programming

### Deliverables
1. Add a primitive to RL-RTX API to return the number of active tasks in the system.
    <strong>int os_tsk_count_get (void);</strong>
   A task is considered active when its state is not set to INACTIVE in the TCB. The
   os idle task is a valid task that you should check the state as well.
   
2. Implement a new primitive to obtain the task status information from the RTX at
   runtime given the task id. The function description is as follows.
    <strong>OS_RESULT os_tsk_get (OS_TID task_id, RL_TASK_INFO *buffer)</strong>
   The primitive returns information about a task. The system call returns a rl_task_info
   structure , which contains the following fields:
    <strong>typedef struct rl_task_info {
    U8 state; /* Task state */
    U8 prio; /* Execution priority */
    U8 task_id; /* Task ID value for optimized TCB access */
    U8 stack_usage; /* Stack usage percent value. eg.=58 if 58% */
    void (*ptask)(); /* Task entry address */
    26
    } RL_TASK_INFO;</strong>
   The state field describes the state of this task and is one of INACTIVE, READY,RUNNING,
   WAIT_DLY, WAIT_SEM, and WAIT_MUT. These states are described in details in the RLARM

   The prio field describes the priority of this task.
   The task_id field describes the id of task assigned by the OS.
   The stack_usage describes how much stack space is used by this task. The value is
   the percent value. For example, if 58% of this task stack is used, stack_usage is set
   to 58.
   The ptask field describes the entry address of this task function.
   The function returns OS_R_OK on success and OS_R_NOK otherwise.

3. Create five testing tasks to demonstrate that you have successfully implemented the
   required primitives Your test tasks should do the following tests.
   • One of the tasks calls the os_tsk_count_get primitive to test the number of
     active tasks in the system returned by the function.
   • One of the tasks periodically prints task status of each task in the system by
     calling the os_tsk_get primitive.
