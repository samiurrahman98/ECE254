/*----------------------------------------------------------------------------
 *      ECE254 Lab Task Management
 *----------------------------------------------------------------------------
 *      Name:    RT_MEMBOX_EXT.H
 *      Purpose: Interface functions for blocking 
 *               fixed memory block management system
 *      Rev.:    V4.60
 *----------------------------------------------------------------------------
 *      This code extends the RealView Run-Time Library.
 *      Created by University of Waterloo ECE254 Lab Staff.
 *---------------------------------------------------------------------------*/
/* Variables */

/* Functions */
extern void     *rt_mem_alloc (void *mem_pool);
extern OS_RESULT rt_mem_free  (void *mem_pool, void *box);

/* task sate user level macro added in ECE254 lab1 keil_proc */
#define INACTIVE        0
#define READY           1
#define RUNNING         2
#define WAIT_DLY        3
#define WAIT_ITV        4
#define WAIT_OR         5
#define WAIT_AND        6
#define WAIT_SEM        7
#define WAIT_MBX        8
#define WAIT_MUT        9
#define WAIT_MEM        10

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

