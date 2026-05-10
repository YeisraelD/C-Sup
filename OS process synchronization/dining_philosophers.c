#include <pthread.h>   // Library for POSIX thread creation and management
#include <semaphore.h> // Library for semaphore synchronization primitives
#include <stdio.h>     // Standard I/O library for printing output
#include <stdlib.h>    // Standard library for memory allocation
#include <unistd.h>    // Unix standard header for sleep functions

#define N 5            // Number of philosophers
#define THINKING 2     // State representing philosopher is thinking
#define HUNGRY 1       // State representing philosopher is trying to get forks
#define EATING 0       // State representing philosopher is eating
#define LEFT (phnum + 4) % N  // Index of the philosopher to the left
#define RIGHT (phnum + 1) % N // Index of the philosopher to the right

int state[N];          // Array to keep track of the state of each philosopher
int phil[N] = {0, 1, 2, 3, 4}; // IDs for the philosophers

sem_t mutex;           // Binary semaphore for mutual exclusion when accessing 'state'
sem_t S[N];            // Array of semaphores, one for each philosopher

// Function to check if a philosopher can start eating
void test(int phnum) {
    // If the philosopher is hungry and neither the left nor right neighbor is eating
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[phnum] = EATING; // Change state to eating

        sleep(2); // Simulate time taken to pick up forks

        printf("[PHILOSOPHER %d] Takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("[PHILOSOPHER %d] Is Eating\n", phnum + 1);
        fflush(stdout);

        // sem_post signals that the philosopher can now proceed to eat
        sem_post(&S[phnum]);
    }
}

// Function to pick up forks (take forks)
void take_fork(int phnum) {
    sem_wait(&mutex); // Enter critical section

    state[phnum] = HUNGRY; // Mark philosopher as hungry
    printf("[PHILOSOPHER %d] Is Hungry\n", phnum + 1);
    fflush(stdout);

    test(phnum); // Try to get forks

    sem_post(&mutex); // Exit critical section

    // If unable to eat, philosopher blocks here until signaled by a neighbor
    sem_wait(&S[phnum]);

    sleep(1); // Simulate eating time
}

// Function to put down forks (put forks)
void put_fork(int phnum) {
    sem_wait(&mutex); // Enter critical section

    state[phnum] = THINKING; // Mark philosopher as thinking
    printf("[PHILOSOPHER %d] Putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("[PHILOSOPHER %d] Is Thinking\n", phnum + 1);
    fflush(stdout);

    // Check if neighbors can eat now that forks are free
    test(LEFT);
    test(RIGHT);

    sem_post(&mutex); // Exit critical section
}

// Thread function for each philosopher
void* philosopher(void* num) {
    while (1) {
        int* i = num;

        sleep(1); // Philosopher is thinking

        take_fork(*i); // Attempt to acquire forks

        sleep(0); // Philosopher is eating

        put_fork(*i); // Release forks and resume thinking
    }
}

int main() {
    pthread_t thread_id[N]; // Array to store thread identifiers

    // Initialize the semaphores
    sem_init(&mutex, 0, 1); // Mutex initialized to 1 (available)

    for (int i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0); // Philosopher semaphores initialized to 0 (blocked)
    }

    printf("--- INITIALIZING DINING PHILOSOPHERS SIMULATION ---\n");
    printf("Number of Philosophers: %d\n\n", N);
    fflush(stdout);

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("[PHILOSOPHER %d] Is Thinking\n", i + 1);
        fflush(stdout);
    }

    // Wait for the threads to finish (in this infinite simulation, they won't)
    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}
