/**
* @file: rt_Task_ext.c
*/
#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_Task.h"
#include "rt_List.h"
#include "rt_Robin.h"
#include "rt_HAL_CM.h"
#include "rt_Task_ext.h"
#include <stdlib.h>

/*----------------------- rt_tsk_count_get --------------------------*/
int rt_tsk_count_get (void) {
	int count = 0;
	int i;
	for (i = 0; i < os_maxtaskrun; i++){
		if (os_active_TCB[i] != INACTIVE)
			count++;
	}
	
	if(os_idle_TCB.state != INACTIVE)
		count++;
	
	return count;
}

/*----------------------- rt_tsk_get --------------------------------*/
OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *p_task_info) {
	P_TCB p_tcb;
	U16 size;
	int memory_used;
	
	if (os_active_TCB[task_id-1] == NULL && task_id != 255){
		return OS_R_NOK;
	}
	
	if (task_id == 255)
		p_tcb = &os_idle_TCB;
	else
		p_tcb = os_active_TCB[task_id-1];
	
	p_task_info->state = p_tcb->state;
	p_task_info->prio = p_tcb->prio;
	p_task_info->task_id = p_tcb->task_id;
	
	size = p_tcb->priv_stack;
  if (size == 0)
    size = os_stackinfo;
	
	if (p_tcb->state != RUNNING)
		memory_used = (&p_tcb->stack[size] - &p_tcb->stack[0]) - ((U32*)p_tcb->tsk_stack - &p_tcb->stack[0]);
	else
		memory_used = (&p_tcb->stack[size] - &p_tcb->stack[0]) - ((U32*)rt_get_PSP() - &p_tcb->stack[0]);
	
	p_task_info->stack_usage = 100.0 * memory_used / size;
	p_task_info->ptask = p_tcb->ptask;
	
	return OS_R_OK;
}