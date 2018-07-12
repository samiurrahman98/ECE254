src/<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Contains the Lab 3 Deliverable<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;processes/<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- produce.c creates separate processes for Producers and Consumers.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- implements the producer-consumer paradigm with multiple processes and message queues.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- compile with: gcc produce.c -lrt -lm -o produce.out<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;threads/<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- produce.c creates separate threads for Producers and Consumers.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- implements the producer-consumer paradigm with multiple threads and a circular buffer.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- compile with: gcc produce.c -pthread -lm -o produce.out
