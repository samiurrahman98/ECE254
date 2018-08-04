## Inter-task Communication and Concurrency in a Linux Environment

Solve the producer-consumer problem with a bounded buffer in a general Linux environment.

This is a classic multi-tasking problem in which there are one or more tasks that create data (these tasks are referred to as "producers") and or more tasks that use the data (these tasks are referred to as "consumers"). We will have a system of P producers and C consumers. Four experimental cases then exist:

• single producer/single consumer<br>
• single producer/multi-consumer<br>
• multi-producer/single consumer<br>
• multi-producer/multi-consumer

The producer tasks will together generate a fixed number, N, integers in total. Each producer will generate a set of integers, one at a time. Since there is more than one producer, and we do not want the producers to have to coordinate their actions since that would require additional inter-task communicaiton, we will adopt the following approach: each producer has an identity number, id, from 0 to P-1; where P is the number of producers. The producer with identity number id will producer the integers i such that i%P == id. For example, if there are 7 producers, the producer with the id = 3 will produce the integers 3, 10, 17, ...; 3%7 = 0 x 7 with a remainder of 3, 10%7 = 1 x 7 with a remainder of 3. Each time a new number is created, it is placed into a fixed-size buffer, size B integers, shared with the consumer tasks. Where there are B integers in the buffer, producers stop producing.

Each consumer is likewise given an integer identity, cid, from 0 to C-1. Each consumer tasks reads the integer out of the buffer, one at a time, and calculates the square root of the integer. When the square root of the integer is itself an integer, the consumer prints out its identity (cid), the original integer taken from the buffer, and the value of the square root on the terminal screen (in Linux) ("cid | original_int | square_root_int"). For example, if there are 6 consumers and consumer with cid = 3 reads the value 16 from the buffer, it will display 3 | 16 | 4. Given that the buffer has a fixed size, B, and assuming that N > B, it is possible for the producers to have produced enough integers that the buffer is filled before any consumer has read any data. If this happens, the producer is blocked, and must wait until there is at least one free spot in the buffer.

Similarly, it is possible for the consumers to read all of the data from the buffer, and yet more data is expected from the producers. In such a case, the consumer is blocked, and must wait for the producers to deposit one or more additoinal integers into the buffer.

Further, if any given producer or consuemr is using the buffer, all other consumers and producers must wait, pending that usage being finished. That is, all access to the buffer represents a critical section, and must be protected as such.

THe program terminates when the consumers have read all N numbers from the producers and finish displaying all square roots that are integers. Note that there is a subtle but complex issue to solve: there are multiple consumers that are reading from the buffer, and thus a mechanisms needs to be established to determine whether or not some consumer has read the last integer (we need this in order to terminate each consumer process).

### Requirements

• Let N be the number of integers the producers should produce in total,<br>
• B be the buffer size,<br>
• P be the number of producers and<br>
• C be the number of consumers.

The producer/consumer system is called with the execution command:<br>
     ./produce <N> <B> <P> <C>
  
The command will execute per the boave description and will then print out the time it took to execute.

Compare the performance of multi-process communication by message queue with multi-thread communication by shared memory.

1. Implement each producer/consumer tasks as a process. Use message queue as the bounded buffer for inter-task communications. You start your program with one process which then forks multiple producer processes and multiple consumer processes. Note that shared memory access is taken care of by the operating system message passing facility. However, kernel memory is finite, and thus there cannot be an unbounded number of messages outstanding; at some point the producer must stop generating messages and the consumer must consume them, otherwise the kernel's memory will be completely consumed with messages, blocking the sender from further progress. What is needed, therefore, it to set up the correct queue size. When the queue is full, the producer is blocked by the system and cannot continue to send messages until a message is consumed.<br>
2. Create a process with a fixed buffer size in which producers and consumers are threads within the process and the buffer is a shared global data structure such as a circular queue that all threads share access to. Note that shared memory access needs to be taken care of at the application level. The POSIX thread sempahore and mutex are to be used for concurrency control.
