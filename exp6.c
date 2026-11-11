#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5
#define LEFT (philosopher_number + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (philosopher_number + 1) % NUM_PHILOSOPHERS

// Define states for philosophers
enum { THINKING, HUNGRY, EATING } state[NUM_PHILOSOPHERS];

// Mutexes and condition variables
pthread_mutex_t mutex;
pthread_mutex_t forks[NUM_PHILOSOPHERS];

// Function prototypes
void *philosopher(void *num);
void take_fork(int philosopher_number);
void put_fork(int philosopher_number);
void test(int philosopher_number);

int main() {
    pthread_t thread_id[NUM_PHILOSOPHERS];
    int philosopher_numbers[NUM_PHILOSOPHERS];

    // Initialize mutexes
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        philosopher_numbers[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &philosopher_numbers[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(thread_id[i], NULL);
    }

    // Destroy mutexes
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

// Philosopher function
void *philosopher(void *num) {
    int philosopher_number = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking\n", philosopher_number + 1);
        sleep(1);  // Thinking

        take_fork(philosopher_number);  // Hungry and try to eat
        sleep(1);  // Eating

        put_fork(philosopher_number);  // Done eating
    }
}

// Function for philosopher to take forks
void take_fork(int philosopher_number) {
    pthread_mutex_lock(&mutex);

    state[philosopher_number] = HUNGRY;
    printf("Philosopher %d is hungry\n", philosopher_number + 1);

    test(philosopher_number);  // Try to pick up forks

    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&forks[philosopher_number]);  // Wait if can't eat
}

// Function for philosopher to put forks back
void put_fork(int philosopher_number) {
    pthread_mutex_lock(&mutex);

    state[philosopher_number] = THINKING;
    printf("Philosopher %d is putting down forks\n", philosopher_number + 1);

    // Test neighbors to see if they can eat
    test(LEFT);
    test(RIGHT);

    pthread_mutex_unlock(&mutex);
}

// Test if philosopher can start eating
void test(int philosopher_number) {
    if (state[philosopher_number] == HUNGRY &&
        state[LEFT] != EATING && state[RIGHT] != EATING) {

        state[philosopher_number] = EATING;
        printf("Philosopher %d is eating\n", philosopher_number + 1);

        pthread_mutex_unlock(&forks[philosopher_number]);
    }
}
