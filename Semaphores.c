#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semaphores
sem_t rw_mutex;
sem_t mutex;
sem_t readTry;

int rc = 0;

void* reader(void* arg) {
    int id = *(int*)arg;

    // Entry Section
    sem_wait(&readTry);
    sem_wait(&mutex);
    rc++;
    if (rc == 1) {
        sem_wait(&rw_mutex);
    }
    sem_post(&mutex);
    sem_post(&readTry);

    // Reading Section
    printf("Reader %d is reading...\n", id);
    sleep(1); 

    // Exit Section
    sem_wait(&mutex);
    rc--;
    if (rc == 0) {
        sem_post(&rw_mutex);
    }
    sem_post(&mutex);

    printf("Reader %d has finished reading.\n", id);
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    // Entry Section
    sem_wait(&readTry);
    sem_wait(&rw_mutex);

    // Writing Section
    printf("Writer %d is writing...\n", id);
    sleep(2);

    // Exit Section
    sem_post(&rw_mutex);
    sem_post(&readTry);

    printf("Writer %d has finished writing.\n", id);
    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    int rid[5] = {1, 2, 3, 4, 5};
    int wid[2] = {1, 2};

    // Initialize Semaphores (0 = thread-shared, 1 = initial value)
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);
    sem_init(&readTry, 0, 1);

    // Create Reader Threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&r[i], NULL, reader, &rid[i]);
    }

    // Create Writer Threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&w[i], NULL, writer, &wid[i]);
    }

    // Join Threads
    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(w[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    sem_destroy(&readTry);

    return 0;
}