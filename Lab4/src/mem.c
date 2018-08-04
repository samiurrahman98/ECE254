/**
 * @file memory.c
 * @brief: ECE254 Lab: memory allocation algorithm comparison template file
 * @author: Samiur Rahman and Nosheen Adil
 * @date: 2018-07-25
 */

/* Includes */
#include <stdio.h> 
#include <stdlib.h> 
#include "mem.h"
#include <math.h>
#include <limits.h>

/* Defines */
#define BLOCK_SIZE 4

/* Structs */
struct Memory_Allocation_Algorithm_Struct {
    void* memory_box;
    void* free_space;
    int* bit_array;
    int num_blocks;
};

/* Global Variables */
struct Memory_Allocation_Algorithm_Struct Best;
struct Memory_Allocation_Algorithm_Struct Worst;

/* Bit Array Functions */

/* Set the bit at the index-th position in array[index] */
void SetBit(int array[], int index) {
    array[index/32] |= 1 << (index % 32);
}

/* Clear the bit at the index-th position in array[index] */
void ResetBit(int array[], int index) {
    array[index/32] &= ~(1 << (index % 32));
}

/* Return bit at index-th position in array[index] */
int TestBit(int array[], int index) {
    return ((array[index/32] & (1 << (index % 32))) != 0);
}

/* Memory initializer */
int best_fit_memory_init(size_t size)
{
    printf("~~Best fit - attempting to initialize %d bytes.~~\n", (int) size);

	if (size < BLOCK_SIZE) {
        printf("~~Returning -1.~~\n\n");
        return -1;
    }

    printf("~~Initializing %d bytes of memory.~~\n", (int) size);

	Best.memory_box = malloc(size);
	Best.bit_array = (int*) Best.memory_box;

	/* number of blocks being tracked */
	Best.num_blocks = (int)(ceil((float)size/(float)BLOCK_SIZE));

    /* number of blocks takes x # of bits to represent */
    int x = ceil(log2f(Best.num_blocks));

    printf("~~# of blocks: %d, # of bits required to represent the # of blocks: %d~~\n",
            Best.num_blocks, x);

	int i;
	for (i = 0; i < Best.num_blocks; i++) {
	   if (i < x ) SetBit(Best.bit_array, i);
       else ResetBit(Best.bit_array, i);
    }

    for (i = 0; i < Best.num_blocks; i++)
        printf("%d", TestBit(Best.bit_array, i));
    printf("\n");
	
    Best.free_space = Best.memory_box + x;
	return 0;
}

int worst_fit_memory_init(size_t size)
{
    printf("~~Worst fit - attempting to initialize %d bytes.~~\n", (int) size);

    if (size < BLOCK_SIZE) {
        printf("~~Returning -1.~~\n\n");
        return -1;
    }

    printf("~~Initializing %d bytes of memory.~~\n", (int) size);

	Worst.memory_box = malloc(size);
	Worst.bit_array = (int*) Worst.memory_box;

	/* number of blocks being tracked */
	Worst.num_blocks = (int)(ceil((float)size/(float)BLOCK_SIZE));

    /* number of blocks takes x # of bits to represent */
    int x = ceil(log2f(Worst.num_blocks));

    printf("~~# of Blocks: %d, # of bits required to represent the # of blocks: %d~~\n",
            Worst.num_blocks, x);

	int i;
	for (i = 0; i < Worst.num_blocks; i++) {
	   if (i < x ) { SetBit(Worst.bit_array, i); }
       else { ResetBit(Worst.bit_array, i); }
    }

    for (i = 0; i < Worst.num_blocks; i++)
        printf("%d", TestBit(Worst.bit_array, i));
    printf("\n");
	
	Worst.free_space = Worst.memory_box + x;
	return 0;
}

/* Memory allocators */
void *best_fit_alloc(size_t size) {

    /* Each allocation requires 1 block before the actual allocation to store the number of blocks allocated */

    printf("~~Best fit - attempting to allocate %d bytes.~~\n", (int) size);
    
    int required_blocks = (int)(ceil((float)size/(float)BLOCK_SIZE));

    if (size < BLOCK_SIZE || Best.num_blocks < required_blocks + 1) {
        printf("~~Returning null.~~\n\n");
        return NULL;
    }

    int start = 0;
    int best_size = INT_MAX;
    int track_index;
    int in_contiguous_section = 0;
    int contiguous_section_length = 0;
    
    /* Find the smallest contiguous set of 0s greater than 1 + the number of blocks required for allocation */
    int i;
    for (i = 0; i < Best.num_blocks; i++) {
        /* entering a contiguous section */
        if (TestBit(Best.bit_array, i) == 0 && !in_contiguous_section) {
            in_contiguous_section = 1;
            track_index = i;
        }

        /* in a contiguous section */
        if (TestBit(Best.bit_array, i) == 0 && in_contiguous_section) contiguous_section_length++;

        /* leaving a contiguous section */
        if (((TestBit(Best.bit_array, i) == 1 && in_contiguous_section)) || i == Best.num_blocks - 1) {
            in_contiguous_section = 0;
            if ((contiguous_section_length < best_size) && (contiguous_section_length - required_blocks > 0)) {
                best_size = contiguous_section_length;
                start = track_index;
            }
            contiguous_section_length = 0;
        }
    }

    /* If unable to find a large enough contiguous block, terminate */
    if (best_size == INT_MAX || best_size < required_blocks + 1) {
        printf("~~Returning null.~~\n\n");
        return NULL;
    }

    if (best_size > required_blocks + 1) best_size = required_blocks + 1;

    printf("~~Best fit - allocated 1 + %d blocks.~~\n", (int) required_blocks);

    /* Else mark all the blocks in the best contiguous block as used */
    for (i = start; i < start + best_size; i++)
        SetBit(Best.bit_array,i);

    for (i = 0; i < Best.num_blocks; i++)
        printf("%d", TestBit(Best.bit_array,i));
    printf("\n");

    /* Mark the first (extra) block of the best contiguous block with the size of the memory being allocated */
    void *temp = Best.free_space + (start * BLOCK_SIZE);
    int* size_block = (int*) temp;
    *size_block = best_size;
 
	return Best.free_space + ((start + 1) * BLOCK_SIZE);
}


void *worst_fit_alloc(size_t size) {

    printf("~~Worst fit - attempting to allocate %d bytes.~~\n", (int) size);

    int required_blocks = (int)(ceil((float)size/(float)BLOCK_SIZE));
    if (size < BLOCK_SIZE || Worst.num_blocks < required_blocks + 1) {
        printf("~~Returning null.~~\n\n");
        return NULL;
    }
    
    int start = 0;
    int worst_size = 0;
    int track_index = 0;
    int in_contiguous_section = 0;
    int contiguous_section_length = 0;

    /* Find the largest contiguous set of 0s */
    int i;
    for (i = 0; i < Worst.num_blocks; i++) {
        /* entering a contiguous section */
        if (TestBit(Worst.bit_array, i) == 0 && !in_contiguous_section) {
            in_contiguous_section = 1;
            track_index = i;
        }

        /* in a contiguous section */
        if (TestBit(Worst.bit_array, i) == 0 && in_contiguous_section) contiguous_section_length++;

        /* leaving a contiguous section */
        if (((TestBit(Worst.bit_array, i) == 1 && in_contiguous_section)) || i == Worst.num_blocks - 1) {
            in_contiguous_section = 0;
            if (contiguous_section_length > worst_size && contiguous_section_length > required_blocks) {
                worst_size = contiguous_section_length;
                start = track_index;
            }
            contiguous_section_length = 0;
        }
    }

    /* If there is no free space or the quantity of free space is less than the number of required blocks, return null */
    if (worst_size == 0 || worst_size < required_blocks + 1) {
        printf("~~Returning null.~~\n\n");
        return NULL;
    }

    if (worst_size > required_blocks + 1) worst_size = required_blocks + 1;

    printf("~~Worst fit - allocated 1 + %d blocks.~~\n", (int) required_blocks);

    /* Else mark all the blocks in the worst contiguous block as used */
    for (i = start; i < start + worst_size; i++)
        SetBit(Worst.bit_array, i);

    for (i = 0; i < Worst.num_blocks; i++)
        printf("%d", TestBit(Worst.bit_array,i));
    printf("\n");

    /* Mark the first (extra) block of the best contiguous block with the size of the memory being allocated */
    void *temp = Worst.free_space + (start * BLOCK_SIZE);
    int* size_block = (int*) temp;
    *size_block = worst_size;

    return Worst.free_space + ((start + 1) * BLOCK_SIZE);
}

/* memory de-allocator */
void best_fit_dealloc(void *ptr) {
    if (ptr == NULL) return;

    int* user_mem_start = (int*) ptr;
    int* block_mem_start = user_mem_start - 1;
    int block_size = *block_mem_start;
	
	int block_index = block_mem_start - (int*) Best.free_space;

    if (TestBit(Best.bit_array, block_index) == 0) {
        printf("~~Memory not currently allocated. Returning.~~\n\n");
        return;
    }

    printf("~~Best fit - deallocated %d blocks.~~\n", block_size);

    int i;
    for (i = block_index; i < block_index + block_size; i++)
        ResetBit(Best.bit_array, i);
    
    for (i = 0; i < Best.num_blocks; i++)
        printf("%d", TestBit(Best.bit_array, i));
    printf("\n");
}

void worst_fit_dealloc(void *ptr) {
    if (ptr == NULL) return;

    int* user_mem_start = (int*) ptr;
    int* block_mem_start = user_mem_start - 1;
    int block_size = *block_mem_start;

    int block_index = block_mem_start - (int*) Worst.free_space;

    if (TestBit(Worst.bit_array, block_index) == 0) {
        printf("~~Memory not currently allocated. Returning.~~\n\n");
        return;
    }

    printf("~~Worst fit - deallocated %d blocks.~~\n", block_size);

    int i;
    for (i = block_index; i < block_index + block_size; i++)
        ResetBit(Worst.bit_array, i);

    for (i = 0; i < Worst.num_blocks; i++)
        printf("%d", TestBit(Worst.bit_array, i));
    printf("\n");
}

/* memory algorithm metric utility function(s) */

/* count how many free blocks are less than the input size */ 
int best_fit_count_extfrag(size_t size) {
    if (size < BLOCK_SIZE) {
        printf("~~Returning -1.~~\n\n");
        return -1;
    }
    
    int required_blocks = (int)(ceil((float)size/(float)BLOCK_SIZE));
    int in_contiguous_section = 0;
    int contiguous_section_length = 0;
    int fragment_count = 0;

    int i;
    for (i = 0; i < Best.num_blocks; i++) {
        /* entering a contiguous section */
        if (TestBit(Best.bit_array, i) == 0 && !in_contiguous_section) in_contiguous_section = 1;

        /* in a contiguous section */
        if (TestBit(Best.bit_array, i) == 0 && in_contiguous_section) contiguous_section_length++;

        /* leaving a contiguous section */
        if ((TestBit(Best.bit_array, i) == 1 && in_contiguous_section) || i == Best.num_blocks - 1) {
            in_contiguous_section = 0;
            if (contiguous_section_length < required_blocks + 1) fragment_count++;
            contiguous_section_length = 0;
        }
    }
	return fragment_count;
}

int worst_fit_count_extfrag(size_t size) {
    if (size < BLOCK_SIZE) {
        printf("~~Returning -1.~~\n\n");
        return -1;
    }

    int required_blocks = (int)(ceil((float)size/(float)BLOCK_SIZE));
    int in_contiguous_section = 0;
    int contiguous_section_length = 0;
    int fragment_count = 0;

    int i;
    for (i = 0; i < Worst.num_blocks; i++) {
        /* entering a contiguous section */
        if (TestBit(Worst.bit_array, i) == 0 && !in_contiguous_section) in_contiguous_section = 1;

        /* in a contiguous section */
        if (TestBit(Worst.bit_array, i) == 0 && in_contiguous_section) contiguous_section_length++;

        /* leaving a contiguous section */
        if ((TestBit(Worst.bit_array, i) == 1 && in_contiguous_section) || i == Worst.num_blocks - 1) {
            in_contiguous_section = 0;
            if (contiguous_section_length < required_blocks + 1) fragment_count++;
            contiguous_section_length = 0;
        }
    }
    return fragment_count;
}