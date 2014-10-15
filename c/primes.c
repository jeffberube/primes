/*
 * @Author:	Jeff Berube
 * @Title:	Primes
 *
 * @Usage	./primes <MAX> <NUMTHREADS>
 *
 * 		<MAX>		Maximum number to calculate primes to
 * 		<NUMTHREADS>	Number of threads to split the workload amongst
 *
 * @Description:	Calculates primes from 1 to MAX using NUMTHREADS threads.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int max, numthreads;

pthread_mutex_t lock;

/*
 * sieve
 * 
 * Thread function. Parameter is an int between 0 and NUMTHREADS that refers to the interval the
 * thread will operate on.
 *
 */

void *sieve(void *param) {

	/* Variables */
	int flag = 0;
	int threadnum = (int)param ;
	int interval_size = max / numthreads;
	int start = (threadnum * interval_size) + 1;
	int end = (threadnum + 1) * interval_size;
	struct timeval t_start, t_end;

	/* Allocate space to store all primes */
	int *primes = malloc((interval_size / 2) * sizeof(int));
	int index = 0;

	/* If last thread and range doesn't divide nicely by NUMTHREADS */
	if (threadnum == numthreads - 1 && max % interval_size) end += max % numthreads;
	
	/* This is where the magic happens */
	int i, j;	

	/* Start timer for thread runtime */
	gettimeofday(&t_start);

	for (i = start; i < end; ++i) {

		flag = 0;

		for (j = 2; j <= i/2; ++j) {

			if (i % j == 0) {
				flag = 1;
				break;
			}

		}

		if (!flag) {
			
			*(primes + index) = i;
			index++;

		}

	}

	/* End timer for thread runtime */
	gettimeofday(&t_end);

	/* Enter critical output region */
	pthread_mutex_lock(&lock);

	/* Show thread stats */
	printf("\n\nThread: %d \tStart: %d \tEnd: %d \tRuntime: %lu\xC2\xB5s\n", 
			threadnum + 1, start, end, t_end.tv_usec - t_start.tv_usec);
	
	/* Dump primes */
	printf("Primes: ");

	i = 0;
	
	while (i < index) {
	
		printf("%d ", *(primes + i));
		i++;

	}

	pthread_mutex_unlock(&lock);

	/* Exit critical region */

	free(primes);

}

int main (int argc, char *argv[]) {

	/* Arguments */
	max = atoi(argv[1]);
	numthreads = atoi(argv[2]);
	
	pthread_t *threads = malloc(numthreads * sizeof(pthread_t));

	/* Thread variables */
	pthread_t tid;
	pthread_attr_t attr;

	/* Test error conditions */
	if (argc != 3) {
	
		fprintf(stderr, "Usage: primes <max> <numthreads>\n");
		return -1;

	} else if (max < 10) {

		fprintf(stderr, "You must enter a number greater than 10 as the upper bound.\n");
		return -1;

	} else if (numthreads >= max / 2) {

		fprintf(stderr, "Number of threads must be less than half of MAX.\n");
		return -1;		

	} else if (numthreads > 50) {
	
		fprintf(stderr, "Maximum number of threads is 50.");
		return -1;
	}

	/* Init mutex */
	if (pthread_mutex_init(&lock, NULL) != 0) {
	
		printf("Mutex init failed. Try restarting.");
		return -1;

	}

	/* Initiate and create thread */
	pthread_attr_init(&attr);

	int i = 0;

	while (i < numthreads) {
		
		pthread_create(threads + i, &attr, sieve, (void *)i);
		i++;
	}


	i = 0;

	while (i < numthreads) {

		pthread_join(*(threads + i), NULL);
		i++;

	}
	
	pthread_mutex_destroy(&lock);

	printf("\n\n");

	return  0;

}
