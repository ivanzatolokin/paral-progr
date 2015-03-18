#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include <omp.h>
#include <iostream>
using namespace std;

#define NUM_THREADS     20
const int size = 2000;
int a[size][size];
int b[size][size];
int c[size][size];
pthread_cond_t cv;
pthread_mutex_t mtx;
bool thread4done = false;

void *task_code(void *argument)
{
	int tid;

	tid = *((int *)argument);

	//pthread_mutex_lock(&mtx);

	for (int k = size / NUM_THREADS * tid; k < size / NUM_THREADS*(tid + 1); k++) {
		for (int i = 0; i < size; i++) {
			int sum = 0;
			for (int j = 0; j < size; j++) {
				sum += a[i][j] * b[j][k];
			}
			c[i][k] = sum;
		}
	}

	//pthread_mutex_unlock(&mtx);

	/* optionally: insert more useful stuff here */

	return NULL;
}


int main(void)
{
	pthread_t threads[NUM_THREADS];
	int thread_args[NUM_THREADS];
	int rc = 0, i = 0;

	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cv, NULL);

	int sum;

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++)
			a[i][j] = rand() % 60 + 20;
	}
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++)
			b[i][j] = rand() % 60 + 20;
	}

	printf("Hello from POSIX threads app!\n");

	//double begin = omp_get_wtime();

	// create all threads one by one
	for (i=0; i < NUM_THREADS; i++)
	{
		thread_args[i] = i;
		printf("In main: creating thread %d\n", i);
		rc = pthread_create(&threads[i], NULL, task_code, (void *)&thread_args[i]);
		assert(0 == rc);
	}

	//cout << "Vremya sozdaniya potokov - " << (omp_get_wtime() - begin) << endl;

	// wait for each thread to complete
	for (i = 0; i < NUM_THREADS; ++i) {
		// block until thread i completes
		rc = pthread_join(threads[i], NULL);
		printf("In main: thread %d is complete\n", i);
		assert(0 == rc);
	}

	//cout << "Vremya rabotu parallel'nogo vupolneniya - " << (omp_get_wtime() - begin) << endl;

	/*cout << "Матрица C" << endl;
	for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
	cout << c[i][j] << " ";
	}
	cout << endl;
	}*/

	/*pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cv);*/

	return EXIT_SUCCESS;
}
