#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max, numthreads;

/*
 * sieve
 * 
 * Thread function. Parameter is an int between 0 and NUMTHREADS that refers to the interval the
 * thread will operate on.
 *
 */

void *sieve(void *param) {

	int flag = 0;
	int threadnum = (int)param ;
	int interval_size = max / numthreads;
	int start = (threadnum * interval_size) + 1;
	int end = (threadnum + 1) * interval_size;

	/* If last thread and range doesn't divide nicely by NUMTHREADS */
	if (threadnum == numthreads - 1 && max % interval_size) end += max % numthreads;
	
	printf("Thread: %d \tStart: %d \tEnd: %d\n", threadnum, start, end);
	
	printf("Primes: ");

	int i, j;	

	for (i = start + 1; i < end; ++i) {

		flag = 0;

		for (j = 2; j <= i/2; ++j) {

			if (i % j == 0) {
				flag = 1;
				break;
			}

		}

		if (!flag) printf("%d ", i);

	}

	printf("\n\n");

}

int main (int argc, char *argv[]) {

	/* Arguments */
	max = atoi(argv[1]);
	numthreads = atoi(argv[2]);
	
	pthread_t *threads = malloc(numthreads * sizeof(pthread_t));

	/* Thread variables */
	pthread_t tid;
	pthread_attr_t attr;

	/* If the number of arguments isn't correct */
	if (argc != 3) {
	
		fprintf(stderr, "Usage: primes <max> <numthreads>\n");
		return -1;

	}

	if (max < 2) {

		fprintf(stderr, "You must enter a number greater than 1 as the upper bound");
		return -1;

	}

	if (numthreads > max) {

		

	}

	/* Initiate and create thread */
	pthread_attr_init(&attr);

	int i = 0;

	while (i < numthreads) {
		
		pthread_create(threads + i, &attr, sieve, i);
		i++;
	}

	i = 0;

	while (i < numthreads) {

		pthread_join(*(threads + i), NULL);

	}


	return  0;

}
