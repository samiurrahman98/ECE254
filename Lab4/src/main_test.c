/**
  * ECE254 Linux Dynamic Memory Management Lab
  * @file: main_test.c
  * @brief: The main file to write tests of memory allocation algorithms
  */ 

/* includes */
/* system provided header files. You may add more */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/* non-system provided header files. 
   Do not include more user-defined header files here
 */
#include "mem.h"

void default_best_fit_test();
void default_worst_fit_test();
void custom_best_fit_test();
void custom_worst_fit_test();
void custom_comparison_test();

int main(int argc, char *argv[])
{
	int test_case; // default algorithm to test is best fit

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <0/1/2/3/4>. 0 for default best fit test and 1 for default worst fit test.\n 2 for custom best fit test and 3 for custom worst fit test.\n", argv[0]);
		exit (1);
	}

    test_case = atoi(argv[1]);
    struct timeval tv;
	double running_time[2];
	
	if ( test_case == 0 ) default_best_fit_test();
    else if ( test_case == 1 ) default_worst_fit_test();
    else if ( test_case == 2 ) {
        // initialize start time and store its value
	    gettimeofday(&tv, NULL);
	    running_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.0;

        custom_best_fit_test();

        // initialize end time and store its value
        gettimeofday(&tv, NULL);
        running_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

        printf("System execution time: %.6lf seconds\n", \
            running_time[1] - running_time[0]);
    }
	else if ( test_case == 3) {
        // initialize start time and store its value
	    gettimeofday(&tv, NULL);
	    running_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.0;

        custom_worst_fit_test();

        // initialize end time and store its value
        gettimeofday(&tv, NULL);
        running_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

        printf("System execution time: %.6lf seconds\n", \
            running_time[1] - running_time[0]);
    }
	else {
		fprintf(stderr, "Should not reach here!\n");
		exit(1);
	}
	return 0;
}

void default_best_fit_test() {
    void *p;
    int num = 0;

    best_fit_memory_init(1024);	// init 1KB, best fit

    p = best_fit_alloc(8);		// allocate 8B
    printf("~~Best fit: p=%p~~\n", p);

    if ( p != NULL ) best_fit_dealloc(p);

    num = best_fit_count_extfrag(4);
    printf("~~External frag: %d~~\n", num);
}

void default_worst_fit_test() {
    void *q;
    int num = 0;

    worst_fit_memory_init(1024);	// init 1KB, worst fit

    q = worst_fit_alloc(8);		// allocate 8B
    printf("~~Worst fit: q=%p~~\n", q);

    if ( q != NULL ) worst_fit_dealloc(q);

    num = worst_fit_count_extfrag(4);
    printf("~~External frag: %d~~\n", num);
}

void custom_best_fit_test() {
    void *pointers[10];
    int num;

    printf("INIT BEST FIT TEST RUN.\n\n");

    /* Test Case 1: init memory less than minimum allowed. */
    printf("TEST CASE 1: INIT MEMORY LESS THAN MINIMUM ALLOWED.\n");
    best_fit_memory_init(3);

    best_fit_memory_init(1024);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    /* Test Case 2.1: init alloc memory less than minimum allowed */
    printf("TEST CASE 2.1: INIT ALLOC MEMORY LESS THAN MINIMUM ALLOWED.\n");
    pointers[0] = best_fit_alloc(2);

    /* Test Case 2.2: init alloc memory greater than entire memory space */
    printf("TEST CASE 2.2: INIT ALLOC MEMORY GREATER THAN ENTIRE MEMORY SPACE.\n");
    pointers[0] = best_fit_alloc(1021);

    pointers[0] = best_fit_alloc(763);
    printf("~~Best fit: p=%p~~\n\n", pointers[0]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[1] = best_fit_alloc(8);
    printf("~~Best fit: p=%p~~\n\n", pointers[1]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    best_fit_dealloc(pointers[0]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[2] = best_fit_alloc(544);
    printf("~~Best fit: p=%p~~\n\n", pointers[2]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    // /* Test Case 3: alloc memory greater than available memory space */
    printf("TEST CASE 3: ALLOC MEMORY GREATER THAN AVAILABLE MEMORY SPACE.~~\n");
    pointers[3] = best_fit_alloc(810);

    pointers[4] = best_fit_alloc(24);
    printf("~~Best fit: p=%p~~\n\n", pointers[4]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    best_fit_dealloc(pointers[1]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[5] = best_fit_alloc(200);
    printf("~~Best fit: p=%p~~\n\n", pointers[5]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    /* Test Case 4: dealloc pointer that was already deallocated, consecutively */
    printf("TEST CASE 4: DEALLOC POINTER ALREADY DEALLOCATED, CONSECUTIVELY.~~\n");
    best_fit_dealloc(pointers[2]);
    printf("DUPLICATE DEALLOC UP NEXT, SHOULD SKIP TO NEXT INSTRUCTION.\n");
    best_fit_dealloc(pointers[2]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[6] = best_fit_alloc(56);
    printf("~~Best fit: p=%p~~\n\n", pointers[6]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    best_fit_dealloc(pointers[3]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[7] = best_fit_alloc(482);
    printf("~~Best fit: p=%p~~\n\n", pointers[7]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    best_fit_dealloc(pointers[6]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);
    
    best_fit_dealloc(pointers[4]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[8] = best_fit_alloc(37);
    printf("~~Best fit: p=%p~~\n", pointers[8]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[9] = best_fit_alloc(179);
    printf("~~Best fit: p=%p~~\n", pointers[9]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    best_fit_dealloc(pointers[5]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);
    /* Test Case 5: pass less than minimum value to external frag function */
    printf("TEST CASE 5: PASS LESS THAN MINIMUM VALUE TO EXTERNAL FRAG FUNCTION.~~\n");
    num = best_fit_count_extfrag(1);
    printf("~~External frag: %d~~\n\n", num);

    best_fit_dealloc(pointers[7]);
    num = best_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    printf("END BEST FIT TEST RUN.\n\n");
}

void custom_worst_fit_test() {
    void *pointers[10];
    int num;

    printf("INIT WORST FIT TEST RUN.\n\n");

    /* Test Case 1: init memory less than minimum allowed. */
    printf("TEST CASE 1: INIT MEMORY LESS THAN MINIMUM ALLOWED.\n");
    worst_fit_memory_init(3);

    worst_fit_memory_init(1024);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    /* Test Case 2.1: init alloc memory less than minimum allowed */
    printf("TEST CASE 2.1: INIT ALLOC MEMORY LESS THAN MINIMUM ALLOWED.\n");
    pointers[0] = worst_fit_alloc(2);

    /* Test Case 2.2: init alloc memory greater than entire memory space */
    printf("TEST CASE 2.2: INIT ALLOC MEMORY GREATER THAN ENTIRE MEMORY SPACE.\n");
    pointers[0] = worst_fit_alloc(1021);

    pointers[0] = worst_fit_alloc(763);
    printf("~~Worst fit: p=%p~~\n\n", pointers[0]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[1] = worst_fit_alloc(8);
    printf("~~Worst fit: p=%p~~\n\n", pointers[1]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    worst_fit_dealloc(pointers[0]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[2] = worst_fit_alloc(544);
    printf("~~Worst fit: p=%p~~\n\n", pointers[2]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    // /* Test Case 3: alloc memory greater than available memory space */
    printf("TEST CASE 3: ALLOC MEMORY GREATER THAN AVAILABLE MEMORY SPACE.~~\n");
    pointers[3] = worst_fit_alloc(810);

    pointers[4] = worst_fit_alloc(24);
    printf("~~Worst fit: p=%p~~\n\n", pointers[4]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    worst_fit_dealloc(pointers[1]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[5] = worst_fit_alloc(200);
    printf("~~Worst fit: p=%p~~\n\n", pointers[5]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    /* Test Case 4: dealloc pointer that was already deallocated, consecutively */
    printf("TEST CASE 4: DEALLOC POINTER ALREADY DEALLOCATED, CONSECUTIVELY.~~\n");
    worst_fit_dealloc(pointers[2]);
    printf("DUPLICATE DEALLOC UP NEXT, SHOULD SKIP TO NEXT INSTRUCTION.\n");
    worst_fit_dealloc(pointers[2]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[6] = worst_fit_alloc(56);
    printf("~~Worst fit: p=%p~~\n\n", pointers[6]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    worst_fit_dealloc(pointers[3]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[7] = worst_fit_alloc(482);
    printf("~~Worst fit: p=%p~~\n\n", pointers[7]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    worst_fit_dealloc(pointers[6]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);
    
    worst_fit_dealloc(pointers[4]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[8] = worst_fit_alloc(37);
    printf("~~Worst fit: p=%p~~\n", pointers[8]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    pointers[9] = worst_fit_alloc(179);
    printf("~~Worst fit: p=%p~~\n", pointers[9]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    worst_fit_dealloc(pointers[5]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);
    /* Test Case 5: pass less than minimum value to external frag function */
    printf("TEST CASE 5: PASS LESS THAN MINIMUM VALUE TO EXTERNAL FRAG FUNCTION.~~\n");
    num = worst_fit_count_extfrag(1);
    printf("~~External frag: %d~~\n\n", num);

    worst_fit_dealloc(pointers[7]);
    num = worst_fit_count_extfrag(64);
    printf("~~External frag: %d~~\n\n", num);

    printf("END WORST FIT TEST RUN.\n\n");
}