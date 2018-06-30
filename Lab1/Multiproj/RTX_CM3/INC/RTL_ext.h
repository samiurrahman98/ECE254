/**
* @file: RTL_ext.h
*/
#ifndef __RTL_EXT_H__
#define __RTL_EXT_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
typedef unsigned int U32;
/* Task Identification number. */
typedef U32 OS_TID;
/* Function return of system calls indicating an event or completion state */
typedef U32 OS_RESULT;
	
#if !(__TARGET_ARCH_6S_M || __TARGET_ARCH_7_M || __TARGET_ARCH_7E_M)
/*---------------------------------------------------------------------
* Functions ARM
*-------------------------------------------------------------------*/
#else
/*---------------------------------------------------------------------
* Functions Cortex-M
*-------------------------------------------------------------------*/
#define __SVC_0 __svc_indirect(0)
	
/* task sate user level macro added in ECE254 lab1 */
#define INACTIVE 0
#define READY 1
#define RUNNING 2
#define WAIT_DLY 3
#define WAIT_ITV 4
#define WAIT_OR 5
#define WAIT_AND 6
#define WAIT_SEM 7
#define WAIT_MBX 8
#define WAIT_MUT 9

/* struct rl_task_info added in ECE254 lab1 */
typedef struct rl_task_info {
U8 state; /* Task state */
U8 prio; /* Execution priority */
U8 task_id; /* Task ID value for optimized TCB access */
U8 stack_usage; /* Stack usage percent value */
void (*ptask)(); /* Task entry address */
} RL_TASK_INFO;

/* ECE254 Comment: added for lab1 */
extern int rt_tsk_count_get(void);
#define os_tsk_count_get() _os_tsk_count_get((U32)rt_tsk_count_get)
extern int _os_tsk_count_get (U32 p) __SVC_0;

extern OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *p_task_info);
#define os_tsk_get(task_id, p_task_info) _os_tsk_get((U32)rt_tsk_get, task_id, p_task_info)
extern OS_RESULT _os_tsk_get (U32 p, OS_TID task_id, RL_TASK_INFO *p_task_info) __SVC_0;
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !(__TARGET_ARCH_6S_M || __TARGET_ARCH_7_M || __TARGET_ARCH_7E_M)
#endif // !__RTL_EXT_H__
/* end of file */
