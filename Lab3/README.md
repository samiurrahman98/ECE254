src/
    - Contains the Lab 3 Deliverable
    processes/
        - produce.c creates separate processes for Producers and Consumers.
        - implements the producer-consumer paradigm with multiple processes and message queues.
	    - compile with: gcc produce.c -lrt -lm -o produce.out
    threads/
        - produce.c creates separate threads for Producers and Consumers.
        - implements the producer-consumer paradigm with multiple threads and a circular buffer.
        - compile with: gcc produce.c -pthread -lm -o produce.out