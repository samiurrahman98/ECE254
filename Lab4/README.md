## Memory Management in a Linux Environment

Implement two memory allocation algorithms: best fita nd worst fit, andp erform analysis to determine which is better.

For each algorithm, a memory initialization function is implemented, which requests a chunk of free memory dynamically from the system to be managed by different allocation algorithms. Then, an allocation and deallocation function are implemented. One utility function is also to be implemented to help analyze the fficiency of the allocation algorithm and its implementation. A series of tests is then to be written to test the correctness of the implementations.

### Memory initialization functions:
#### Synopsis
<strong>best_fit_memory_init, worst_fit_memory_init</strong> - Initialize dynamic memory to be managed

<strong>int best_fit_memory_init (size_t size);</strong>
<strong>int worst_fit_memory_init (size_t size);</strong>
#### Description
These functions initialize the system with a single block of memory. The name of the function indicates the allocation algorithm to be used. They will always initialize the system as if no memory has been allocated (i.e., all memory is free). The input parameter <strong>size</strong> is the memory size in bytes.

You are to use the <strong>malloc()</strong> funciton inside the initialization function to acquire a chunk of memory of size bytes and then initialize your own memory allocator data structure based on the memory allocation algorithm. Note that <strong>malloc()</strong> can only be used in the initialization function implementation once to request the memory to be managed by your allocator and de-allocator from the system. It should not be used in other places in the code. Instead, you need to implement your own version of allocator without the need of calling <strong>malloc()</strong> again.

<strong>Any memory used for tracking the amount of memory that is either free or allocated will be inside the block of memory that the allocatio nalgorithms are resposible for managing.</strong>
#### Return Value
These functions return 0 on success and -1 on failure.

### Allocation functions:
#### Synopsis
<strong>best_fit_alloc, worst_fit_alloc</strong> - Allocate dynamic memory

<strong>void *best_fit_alloc (size_t size);</strong>
<strong>void *worst_fit_alloc (size_t size);</strong>
#### Description
The input parameter <strong>size</strong> in each allocator is the number of bytes requested from the allocator. Each allocator then returns the starting address of a block of memory of the corresponding size. The memory address should be four bytes aligned. Memory requests may be of any size from one byte all the way up to the full size of memory given in the initialization function. For a request for <strong>N</strong> bytes, return a memory block of (<strong>N + 𝛿</strong>) bytes, where <strong>𝛿</strong> = 0, 1, 2, 3, and (<strong>N + 𝛿</strong>) is a multiple of four. Should <strong>𝛿</strong> &gt; 0, the additional space is just internal fragmentation which may be ignored (and the user will not be told).

If for some reason the memory request cannot be satisfied, such as there being insufficient available memory, a pointer to 0 or <strong>NULL</strong> should be returned. For example, a request of zero bytes will return <strong>NULL</strong>. Recall that the space the structures are needed to maintain un-allocated (free) memory is defined as free space. One subtle point is that because the data structures for managing the memory is counted into the total size of memory initialized, the actual maximum size that is available to allocate to the user is the size of memory initialized minus the space consumed by the memory management data structures. Assuming the system is initialized with <strong>N</strong> bytes, an allocation request of <strong>N</strong> bytes will return <strong>NULL</strong>, for the system requires some space, say <strong>X</strong> (<strong>X</strong> &gt; 0) byte(s) to manage the memory. Similarly, assuming the biggest free memory block has a size of <strong>M</strong> bytes, then a request of <strong>M</strong> bytes may return <strong>NULL</strong>, since the data structure choice may require new space of <strong>X</strong> (<strong>X</strong> &gt; 0) byte(s) to manage these <strong>M</strong> bytes.
#### Return Value
These functions return a pointer to the allocated memory or <strong>NULL</strong> if the request fails.

### Deallocation functions:
#### Synopsis
<strong>best_fit_dealloc, worst_fit_dealloc</strong> - Free dynamic memory

<strong>void best_fit_dealloc (void *ptr);</strong>
<strong>void worst_fit_dealloc (void *ptr);</strong>
#### Description
If the freed memory block is adjacent to other free memory blocks, it is merged with them immediately (i.e., immediate coalescence) and the combined block is then re-integrated into the memory under management. If the input parameters of either function is not an address returned by an allocation function, the behavior of the function is undefined and is left as a free engineering choice. Similarly, if a block is deallocated more than once, without having been allocated in the meantime, the behavior of the function is also undefined.

### Utility functions:
#### Synopsis
<strong>best_fit_count_extfrag, worst_fit_count_extfrag</strong> - Count external fragmented memory blocks

<strong>int best_fit_count_extfrag (size_t size);</strong>
<strong>void worst_fit_count_extfrag (size_t size);</strong>
#### Description
These functions count the number of free memory blocks that are of a size less than the input value of <strong>size</strong>. The input value is in bytes.
