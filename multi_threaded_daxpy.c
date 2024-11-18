#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4
#define VECTOR_SIZE 1000

double a = 2.0;
double x[VECTOR_SIZE], y[VECTOR_SIZE];

void *daxpy(void *arg) {
    int thread_id = *(int *)arg;
    int chunk_size = VECTOR_SIZE / NUM_THREADS;
    int start = thread_id * chunk_size;
    int end = start + chunk_size;

    for (int i = start; i < end; ++i) {
        y[i] = a * x[i] + y[i];
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize vectors (example initialization)
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        x[i] = i;
        y[i] = i;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, daxpy, (void *)&thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // (Optional) Print results for verification
    return 0;
}

