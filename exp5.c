
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10


// Shared buffer
int buffer[BUFFER_SIZE];
int count = 0;  // Current count of items in the buffer

// Semaphores
sem_t empty;    // Tracks empty slots
sem_t full;     // Tracks full slots
pthread_mutex_t mutex;  // Mutex to protect buffer access

void* producer(void* arg) {
    while (1) {
        int item = rand() % 100;  // Produce an item
        sem_wait(&empty);         // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Add item to the buffer
        buffer[count] = item;
        count++;
        printf("Produced %d, Buffer count: %d\n", item, count);

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);            // Signal that there is a new item

        sleep(rand() % 3);  // Sleep to simulate work
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);         // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Remove item from the buffer
        count--;
        int item = buffer[count];
        printf("Consumed %d, Buffer count: %d\n", item, count);

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);            // Signal that there is an empty slot

        sleep(rand() % 3);  // Sleep to simulate work
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // BUFFER_SIZE empty slots
    sem_init(&full, 0, 0);             // 0 full slots
    pthread_mutex_init(&mutex, NULL);  // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (they won't, in this infinite loop example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up (not reached in this example)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
