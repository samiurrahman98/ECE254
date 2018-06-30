/*----------------------------------------------------------------------------
 *      ECE254 Lab Task Management
 *----------------------------------------------------------------------------
 *      Name:    RT_MEMBOX_ext.C
 *      Purpose: Interface functions for blocking 
 *               fixed memory block management system
 *      Rev.:    V4.60
 *----------------------------------------------------------------------------
 *      This code is extends the RealView Run-Time Library.
 *      Created by University of Waterloo ECE254 Lab Staff.
 *---------------------------------------------------------------------------*/
 
/*----------------------------------------------------------------------------
 *      Includes
 *---------------------------------------------------------------------------*/
 
#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_MemBox.h"
#include "rt_HAL_CM.h"
#include "rt_Task.h"       /* added in ECE254 lab keil_proc */ 
#include "rt_MemBox_ext.h" /* added in ECE254 lab keil_proc */   
#include "rt_List.h"
/* ECE254 Lab Comment: You may need to include more header files */

/*----------------------------------------------------------------------------
 *      Global Variables
 *---------------------------------------------------------------------------*/

struct OS_XCB p_queue;
int blocked_count = 0;

/*----------------------------------------------------------------------------
 *      Global Functions
 *---------------------------------------------------------------------------*/

/*==========================================================================*/
/*  The following are added for ECE254 Lab Task Management Assignmet       */
/*==========================================================================*/

/**  
 * os_mem_alloc(mem_pool) calls this function.
 * @brief: Request a block of memory from the memory pool and block the calling
 * 			task if no memory is available in the memory pool
 */
void *rt_mem_alloc (void *mem_pool) {
	void *box;
	int t_id;
	P_TCB calling_task;
	if (mem_pool == NULL) {
		return NULL;
	}
	box = rt_alloc_box(mem_pool);
	if (box == NULL) {
		t_id = rt_tsk_self();
		calling_task = os_active_TCB[t_id - 1];
		rt_put_prio(&p_queue, calling_task);
		rt_block(0xffff, 10);
		blocked_count++;
	}
	return box;
}


/**
 * os_mem_free(mem_pool, box) calls this function.
 * free the memory pointed by box, it will unblock any task that might be 
 * 		waiting for memory.
 * @return: OS_R_OK on success and OS_R_NOK if box does not belong to mem_pool 
 */
OS_RESULT rt_mem_free (void *mem_pool, void *box) {
	int error;
	P_TCB blocked_task;
	if (mem_pool == NULL || box == NULL) {
		return (OS_R_OK);
	}
	error = rt_free_box(mem_pool, box);
	if (error == 0) {
		if (blocked_count > 0) {
			blocked_task = rt_get_first(&p_queue);
			blocked_task->ret_val = (U32)box;
			rt_dispatch(blocked_task);
			blocked_count--;
		}
		return (OS_R_OK);
	}
	return (OS_R_NOK);
}
/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
