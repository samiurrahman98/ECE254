src/<br>
    - Contains the Lab 3 Deliverable<br>
    processes/<br>
        - produce.c creates separate processes for Producers and Consumers.<br>
        - implements the producer-consumer paradigm with multiple processes and message queues.<br>
	    - compile with: gcc produce.c -lrt -lm -o produce.out<br>
    threads/<br>
        - produce.c creates separate threads for Producers and Consumers.<br>
        - implements the producer-consumer paradigm with multiple threads and a circular buffer.<br>
        - compile with: gcc produce.c -pthread -lm -o produce.out
