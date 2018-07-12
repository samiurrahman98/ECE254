/* NOTES:
	Description: Implement the producer-consumer paradigm with multiple processes and message queues.
	Compile with: gcc produce.c -lrt -lm -o produce.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

const char* QUEUE_NAME = "/queue";
int num; // number of items to produce
int maxmsg; // buffer size
int num_p; // number of producers
int num_c; // number of consumers

// open queue for writing, send integers to the queue according to i % num_p == id, close queue and exit process
void producer(int id) {
    mqd_t my_queue = mq_open(QUEUE_NAME, O_WRONLY);
    if (my_queue == -1) {
        perror("Producer - mq_open() operation failed");
        exit(1);
    }

	int i;
    for (i = 0; i < num; i++) {
        if (i % num_p == id) {
            if (mq_send(my_queue, (char *) &i, sizeof(int), 0) == -1) {
                perror("Producer - mq_send() operation failed");
                exit(1);
            }
        }
    }

    mq_close(my_queue);
    exit(0);
}

/* open queue for reading, if there is no error receiving from queue, consumer read point correctly, proceed with calculating 
and printing the square root; if kill signal is received, break out of loop and close queue and exit process */
void consumer(int id) {
    mqd_t my_queue = mq_open(QUEUE_NAME, O_RDWR);

    if (my_queue == -1) {
        perror("Consumer - mq_open() failed");
        exit(1);
    }

    int point, root;

    while (1) {
        if (mq_receive(my_queue, (char *) &point, sizeof(int), NULL) == -1) {
            perror("mq_receive() failed");
            printf("Consumer: %d failed\n", id);
            exit(1);
        } else {
            if (point < 0)
                break;

            root = sqrt(point);
            if (root*root == point) {
                printf("%d %d %d\n", id, point, root);
            }
        }
    }

    mq_close(my_queue);
    exit(0);
}

int main(int argc, char *argv[])
{
	struct timeval tv;
	double g_time[2];

	if (argc != 5) {
		printf("Usage: %s <N> <B> <P> <C>\n", argv[0]);
		exit(1);
	}

	num = atoi(argv[1]);
	maxmsg = atoi(argv[2]);
	num_p = atoi(argv[3]);
	num_c = atoi(argv[4]);

	if (num <= 0 || maxmsg <= 0 || num_p <= 0 || num_c <= 0) {
		printf("Arguments must be positive, non-zero integers\n");
		exit(1);
	}

	// initialize start time and store its value
	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.0;

	// initialize message queue attributes
	mqd_t queue_desc;
	struct mq_attr attributes;
	attributes.mq_maxmsg = maxmsg;
	attributes.mq_msgsize = sizeof( int );
	attributes.mq_flags = 0;
	attributes.mq_curmsgs = 0;

	// create the queue and set permission to all users
	queue_desc = mq_open(QUEUE_NAME, (O_CREAT | O_RDWR), (S_IRWXU | S_IRWXG), &attributes);
	if (queue_desc == -1) {
		perror("Main - mq_open() operation failed\n");
		exit(1);
	}

	// store producer and consumer pids
	pid_t* prod_pid = malloc(num_p * sizeof( pid_t ));
	pid_t* cons_pid = malloc(num_c * sizeof( pid_t ));

	// create num_p producer processes and num_c consumer processes
	int i;
	for (i = 0; i < num_p; i++) {
		prod_pid[i] = fork();
		if (prod_pid[i] < 0)
			printf("Producer %d fork failed\n", i);
		else if (prod_pid[i] == 0) {
			producer(i);
			break;
		}
	}

	for (i = 0; i < num_c; i++) {
		cons_pid[i] = fork();
		if (cons_pid[i] < 0)
			printf("Consumer %d fork failed\n", i);
		else if (cons_pid[i] == 0) {
			consumer(i);
			break;
		}
	}

	// wait for completion of all producers
	int* retval;
	for (i = 0; i < num_p; i++)
		waitpid(prod_pid[i], retval, 0);

	// send kill signals to the queue to terminate all consumers
	int kill = -1;
	for (i = 0; i < num_c; i++) {
		if (mq_send(queue_desc, (char *) &kill, sizeof( int ), 0) == -1) {
			perror("Main - mq_send() operation failed\n");
			exit(1);
		}
	}

	// wait for completion of all consumers
	for (i = 0; i < num_c; i++)
		waitpid(cons_pid[i], retval, 0);

	// close and clean the queue
	if (mq_close(queue_desc) == -1) {
		perror("Main - mq_close() operation failed\n");
		exit(1);
	}

	if (mq_unlink(QUEUE_NAME) != 0) {
		perror("Main - mq_unlink() operation failed\n");
		exit(1);
	}

	free(prod_pid);
	free(cons_pid);

	// initialize end time and store its value
    gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.0;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	
	return 0;
}