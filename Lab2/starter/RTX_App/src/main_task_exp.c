/**
 * @brief: ECE254 Keil ARM RL-RTX Task Management Lab starter file that calls os_tsk_get()
 * @file: main_task_exp.c
 * @date: 2015/09/13
 */
/* NOTE: This release is for students to use */

#include <LPC17xx.h>
#include "uart_polling.h" 
#include <RTL.h>
#include "../../RTX_CM3/INC/RTL_ext.h" /* extended interface header file */
#include <stdio.h>
#include <string.h>

#define NUM_NAMES 6
#define BOX_SIZE 12
#define NUM_BOXES 20

_declare_box(mympool, BOX_SIZE, NUM_BOXES);

struct func_info {
  void (*p)();      /* function pointer */
  char name[16];    /* name of the function */
};

extern void os_idle_demon(void);
__task void task_main(void);
__task void task1(void);
__task void task2(void);
__task void task3(void);
__task void init (void);
 
extern char *state2str(unsigned char state, char *str);
char *fp2name(void (*p)(), char *str);

OS_MUT g_mut_uart;
OS_TID g_tid = 255;

int  g_counter = 0;  // a global counter
char g_str[16];
char g_tsk_name[16];

struct func_info g_task_map[NUM_NAMES] = \
{
  /* os_idle_demon function ptr to be initialized in main */
  {NULL,  "os_idle_demon"}, \
	{task_main, "task_main"},   \
  {task1, "task1"},   \
  {task2, "task2"},   \
	{task3, "task3"},   \
  {init,  "init" }
};

/* no local variables defined, use one global var */

__task void task_main(void)
{
	int x, y, z;
	for (x = 1; x <=3; x++) {
		for (y = 1; y <=3; y++) {
			for (z = 1; z <=3; z++) {
				os_mut_wait(g_mut_uart, 0xFFFF);
				printf("\nTaskMain: Starting test case!\n");
				os_tsk_create(task1, x);
				printf("Task Main: Created task1 with priority %d\n", x);
				os_tsk_create(task2, y);
				printf("Task Main: Created task2 with priority %d\n", y);
				os_tsk_create(task3, z);
				printf("Task Main: Created task3 with priority %d\n", z);
				os_mut_release(g_mut_uart);
				os_dly_wait(8);
				os_mut_wait(g_mut_uart, 0xFFFF);
				printf("TaskMain: Finished test case!\n");
				os_mut_release(g_mut_uart);
			}
		}
	}
	
	os_tsk_delete_self();
}

__task void task1(void)
{
	int i;
	void **boxes[NUM_BOXES];
	OS_RESULT result;
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("Task 1: Starting!\n");
	for (i = 0; i < NUM_BOXES; i++) {
		boxes[i] = os_mem_alloc(mympool);
		if (boxes[i] == NULL) {
			printf("Task 1: Error - Failed to allocate memory box %d in free memory pool\n", i + 1);
		}
	}
	printf("Task 1: Filled entire memory pool\n");
	os_mut_release(g_mut_uart);
	os_dly_wait(4);
	for (i = 0; i < NUM_BOXES; i++) {
		result = os_mem_free(mympool, boxes[i]);
		if (result == OS_R_NOK) {
			os_mut_wait(g_mut_uart, 0xFFFF);
			printf("Task 1: Error - Failed to free memory box %d at %d\n", i + 1, boxes[i]);
			os_mut_release(g_mut_uart);
		}
	}
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("Task 1: Freed entire memory pool\n");
	printf("Task 1: Finished!\n");
	os_mut_release(g_mut_uart);
	os_tsk_delete_self();
}

__task void task2(void)
{
	void *box;
	os_dly_wait(2);
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("Task 2: Starting!\n");
	printf("Task 2: About to be blocked\n");
	os_mut_release(g_mut_uart);
	box = os_mem_alloc(mympool);
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("Task 2: Unblocked, allocated memory box at %d\n", box);
	printf("Task 2: Finished!\n");
	os_mut_release(g_mut_uart);
	os_tsk_delete_self();
}

__task void task3(void)
{
	void *box;
	os_dly_wait(3);
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("Task 3: Starting!\n");
	printf("Task 3: About to be blocked\n");
	os_mut_release(g_mut_uart);
	box = os_mem_alloc(mympool);
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("Task 3: Unblocked, allocated memory box at %d\n", box);
	printf("Task 3: Finished!\n");
	os_mut_release(g_mut_uart);
	os_tsk_delete_self();
}

/*--------------------------- init ------------------------------------*/
/* initialize system resources and create other tasks                  */
/*---------------------------------------------------------------------*/
__task void init(void)
{
	_init_box(&mympool, sizeof(mympool), BOX_SIZE);
	
	os_mut_init(&g_mut_uart);
  
	os_mut_wait(g_mut_uart, 0xFFFF);
	printf("init: the init TID is %d\n", os_tsk_self());
  
	g_tid = os_tsk_create(task_main, 0);
	printf("init: created task_main with TID %d\n", g_tid);
	os_mut_release(g_mut_uart);
  
	os_tsk_delete_self();     /* task MUST delete itself before exiting */
}

/** 
 * @brief: get function name by function pointer
 * @param: p the entry point of a function (i.e. function pointer)
 * @param: str the buffer to return the function name
 * @return: the function name string starting address
 */
char *fp2name(void (*p)(), char *str)
{
	int i;
  
	for ( i = 0; i < NUM_NAMES; i++) {
		if (g_task_map[i].p == p) {
			str = strcpy(str, g_task_map[i].name);  
			return str;
		}
	}
	strcpy(str, "ghost");
	return str;
}

int main(void)
{
	SystemInit();         /* initialize the LPC17xx MCU */
	uart0_init();         /* initialize the first UART */
  
  
	/* fill the fname map with os_idle_demon entry point */
	g_task_map[0].p = os_idle_demon;
  
	printf("Calling os_sys_init()...\n");
	os_sys_init(init);    /* initialize the OS and start the first task */
}
