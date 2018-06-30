/**
* @file: rt_Task_ext.h
*/
typedef struct rl_task_info {
U8 state; /* Task state */
U8 prio; /* Execution priority */
U8 task_id; /* Task ID value for optimized TCB access */
U8 stack_usage; /* Stack usage percent value */
void (*ptask)(); /* Task entry address */
} RL_TASK_INFO;
extern int rt_tsk_count_get(void);
extern OS_RESULT rt_tsk_get(OS_TID task_id, RL_TASK_INFO *p_task_info);
/* end of file */
