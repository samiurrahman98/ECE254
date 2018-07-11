## Introduction to ARM RL-RTX Application and Kernel Programming

### Deliverables
1. Add a primitive to RL-RTX API to return the number of active tasks in the system.
    <p><strong>int os_tsk_count_get (void);</strong></p>
   A task is considered active when its state is not set to INACTIVE in the TCB. The
   os idle task is a valid task that you should check the state as well.
   
2. Implement a new primitive to obtain the task status information from the RTX at
   runtime given the task id. The function description is as follows.
    <p><strong>OS_RESULT os_tsk_get (OS_TID task_id, RL_TASK_INFO *buffer)</strong></p>
   The primitive returns information about a task. The system call returns a rl_task_info
   structure , which contains the following fields:
    <p><strong>typedef struct rl_task_info {<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;U8 state; /* Task state */<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;U8 prio; /* Execution priority */<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;U8 task_id; /* Task ID value for optimized TCB access */<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;U8 stack_usage; /* Stack usage percent value. eg.=58 if 58% */<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void (*ptask)(); /* Task entry address */<br>
    } RL_TASK_INFO;</strong></p>
   The state field describes the state of this task and is one of INACTIVE, READY, RUNNING,
   WAIT_DLY, WAIT_SEM, and WAIT_MUT. These states are described in details in the RL-ARM Real-Time Library User's Guide -> Theory of Operation -> Task Management section.

   The prio field describes the priority of this task.
   The task_id field describes the id of task assigned by the OS.
   The stack_usage describes how much stack space is used by this task. The value is
   the percent value. For example, if 58% of this task stack is used, stack_usage is set
   to 58.
   The ptask field describes the entry address of this task function.
   The function returns OS_R_OK on success and OS_R_NOK otherwise.

3. Create five testing tasks to demonstrate that you have successfully implemented the
   required primitives Your test tasks should do the following tests.<br>
   • One of the tasks calls the os_tsk_count_get primitive to test the number of
     active tasks in the system returned by the function.<br>
   • One of the tasks periodically prints task status of each task in the system by
     calling the os_tsk_get primitive.
