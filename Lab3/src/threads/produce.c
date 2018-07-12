/* NOTES:
	Description: Implement the producer-consumer paradigm with multiple threads and a circular buffer.
    Compile with: gcc produce.c -pthread -lm -o produce
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
#include <pthread.h>
#include <semaphore.h>

int num; // number of items to produce
int maxmsg; // buffer size
int num_p; // number of producers
int num_c; // number of consumers

int producer_index = 0;
int consumer_index = 0;
int total_consumer_index = 0;
int* buffer;

sem_t items;
sem_t spaces;
pthread_mutex_t mutex;

// send integers to the buffer according to i % num_p == producer_id
void *producer(void *id) {
	int* producer_id = (int *) id;
	int i;
	for (i = 0; i < num; i++) {
		if (i % num_p == *producer_id){
			sem_wait(&spaces);
			pthread_mutex_lock(&mutex);
			buffer[producer_index] = i;
			producer_index = (producer_index + 1) % maxmsg;
			pthread_mutex_unlock(&mutex);
			sem_post(&items);
		}
	}
	free(id);
	pthread_exit(0);
} 

// read from buffer if it isn't empty, calculate and print the square root; break out of loop if index is greater than num
void *consumer(void *id) {
	int point, root;
	int* consumer_id = (int *) id;
	while(1) {
		sem_wait(&items);
		pthread_mutex_lock(&mutex);
		point = buffer[consumer_index];
		consumer_index = (consumer_index + 1) % maxmsg;
		total_consumer_index++;
		sem_post(&spaces);
		int root = sqrt(point);

		if (total_consumer_index <= num) {
			if (root*root == point)
				printf("%d %d %d\n", *consumer_id, point, root);
		}

		if (total_consumer_index >= num)
			break;

		pthread_mutex_unlock(&mutex);
	}
	sem_post(&spaces);
    sem_post(&items);
    pthread_mutex_unlock(&mutex);
	free(id);
	pthread_exit(0);
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
	
	buffer = malloc(maxmsg * sizeof( int ));
	pthread_t producers[num_p];
	pthread_t consumers[num_c];
	
	// initialize semaphores
	sem_init(&items, 0, 0);
	sem_init(&spaces, 0, maxmsg);
	pthread_mutex_init(&mutex, NULL);
	
	// create num_p producer threads and num_c consumer threads
	int i;
	for (i = 0; i < num_p; i++) {
		int* producer_id = malloc(sizeof( int ));
		*producer_id = i;
		int created = pthread_create(&producers[i], NULL, producer, producer_id);
		if (created != 0)
			printf("Producer Thread %d not created.\n", i);
	}
	
	for (i = 0; i < num_c; i++) {
		int* consumer_id = malloc(sizeof( int ));
		*consumer_id = i;
		int created = pthread_create(&consumers[i], NULL, consumer, consumer_id);
		if (created != 0)
			printf("Consumer Thread %d not created.\n", i);
	}
	
	// wait for all producer and consumer threads to complete
	for(i = 0; i < num_p; i++)
		pthread_join(producers[i], NULL);
	
	for(i = 0; i < num_c; i++)
		pthread_join(consumers[i], NULL);
	
	// Destroy semaphores items and spaces, and mutex, and free the buffer
	sem_destroy(&items);
	sem_destroy(&spaces);
	pthread_mutex_destroy(&mutex);
	free(buffer);

	// initialize end time and store its value
    gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);
}