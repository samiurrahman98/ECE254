/**
* @file: helloworld.c
* @brief: Two simple tasks running pseduo-parallelly
*/
#include <LPC17xx.h>
#include <RTL.h>
#include <stdlib.h>
#include <stdio.h>
#include "uart_polling.h"

#include "../../RTX_CM3/INC/RTL_ext.h"

OS_TID p_tcb1;
OS_TID p_tcb2;
OS_TID p_tcb3;
OS_TID p_tcb4;
OS_TID p_tcb5;

__task void task1()
{
	int num = 0;
	while(1)
	{
		num = os_tsk_count_get();
		printf("Number of tasks: %d. \n\n", num);
		os_dly_wait(50);
	}
}

__task void task2()
{	
	// Fill stack with identifying values
	U8 t[240];
	U32 i = 0;
	
	// Fill the stack with 0xAA's (see in Memory window of debugger)
	t[0] = 0xAA;
	for(i = 1; i < sizeof(t)/sizeof(U8); i++) {
		t[i] = t[i-1];
	}
	
	// Keep the task running forever
	for(i = 0; ; i++){
		os_dly_wait(50);
	}
}

__task void task3()
{	
	// Fill stack with identifying values
	U8 t[360];
	U32 i = 0;
	
	// Fill the stack with 0xAA's (see in Memory window of debugger)
	t[0] = 0xAA;
	for(i = 1; i < sizeof(t)/sizeof(U8); i++) {
		t[i] = t[i-1];
	}
	
	// Keep the task running forever
	for(i = 0; ; i++){
		os_dly_wait(50);
	}
}

__task void task4()
{	
	// Fill stack with identifying values
	U8 t[480];
	U32 i = 0;
	
	// Fill the stack with 0xAA's (see in Memory window of debugger)
	t[0] = 0xAA;
	for(i = 1; i < sizeof(t)/sizeof(U8); i++) {
		t[i] = t[i-1];
	}
	
	// Keep the task running forever
	for(i = 0; ; i++){
		os_dly_wait(50);
	}
}

__task void task5()
{
	RL_TASK_INFO p_task_info;
	int i;
	
	while(1){
		
		for(i = 2; i <= 6; i++) {
			os_tsk_get(i, &p_task_info);
			printf("State: %d. \n", p_task_info.state);
			printf("Priority: %d. \n", p_task_info.prio);
			printf("Task ID: %d. \n", p_task_info.task_id);			
			printf("Stack Usage: %d. \n", p_task_info.stack_usage);
			printf("Ptask: %x. \n\n", p_task_info.ptask);
		}
		
		os_tsk_get(255, &p_task_info);
		printf("State: %d. \n", p_task_info.state);
		printf("Priority: %d. \n", p_task_info.prio);
		printf("Task ID: %d. \n", p_task_info.task_id);			
		printf("Stack Usage: %d. \n", p_task_info.stack_usage);
		printf("Ptask: %x. \n\n", p_task_info.ptask);

		os_dly_wait(50);
	}
}

__task void init(void)
{
	p_tcb1 = os_tsk_create(task1, 1); // task1 at priority 1
	p_tcb2 = os_tsk_create(task2, 2); // task2 at priority 2
	p_tcb3 = os_tsk_create(task3, 3); // task3 at priority 3
	p_tcb4 = os_tsk_create(task4, 4); // task4 at priority 4
	p_tcb5 = os_tsk_create(task5, 5); // task5 at priority 5	
	os_tsk_delete_self(); // must delete itself before exiting
}

int main ()
{
	SystemInit();
	uart0_init();
	os_sys_init(init);
}
