#include <stdio.h>     // Standard I/O library for console messaging
#include <stdlib.h>    // Standard library for dynamic memory management
#include <unistd.h>    // Unix standard header for sleep functions
#include <pthread.h>   // POSIX thread library for concurrent execution
#include <semaphore.h> // Semaphore library for thread synchronization

#define CHAIRS 5           // Maximum capacity of the waiting room chairs
#define TOTAL_CUSTOMERS 5   // Reduced customer count for quick demonstration

sem_t customers;           // Semaphore to signal barber that a customer is present
sem_t barber;             // Semaphore to signal customer that barber is ready
pthread_mutex_t mutex;     // Mutex to protect the shared 'waiting' variable
int waiting = 0;           // Global shared state for customers in the shop

// Logic for the Barber thread (The source of the deadlock)
void* barber_function(void* arg) {
    while (1) { // Simulation of the barber's infinite work loop
        printf("[BARBER] Attempting to lock mutex...\n"); // Debug message before locking
        pthread_mutex_lock(&mutex); // !!! FAULTY STEP: Acquire lock BEFORE checking for customers
        
        printf("[BARBER] Mutex locked. Now waiting for a customer (This will cause DEADLOCK)...\n");
        fflush(stdout); // Ensure the above message is printed immediately

        /* 
         * DEADLOCK CAUSE: 
         * The barber calls sem_wait() while holding the mutex. 
         * He is now blocked/asleep, but he still has the "key" (mutex) to the shop.
         * No customer can ever enter the shop because they need this mutex to check for chairs.
         */
        sem_wait(&customers); 

        waiting--; // Decrement waiting count (This line will never be reached)
        sem_post(&barber); // Signal customer (This line will never be reached)
        pthread_mutex_unlock(&mutex); // Release lock (This line will never be reached)

        printf("[BARBER] Cutting hair...\n"); // Service simulation
        sleep(2); // Simulate 2 seconds of work
    }
    return NULL;
}

// Logic for the Customer threads (The victims of the deadlock)
void* customer_function(void* arg) {
    int id = *(int*)arg; // Extract unique customer ID
    free(arg); // Free allocated memory for the ID

    printf("[CUSTOMER %d] Arrived. Trying to lock mutex to check for chairs...\n", id);
    fflush(stdout); // Force output to terminal

    /*
     * HANGING POINT:
     * The customer thread stops here forever. It is waiting for the mutex lock,
     * but the Barber is asleep and holding it, so it will never be released.
     */
    pthread_mutex_lock(&mutex); 

    if (waiting < CHAIRS) { // Check if a seat is available
        waiting++; // Take a seat
        printf("[CUSTOMER %d] Entering shop...\n", id); // Success message
        sem_post(&customers); // Signal the barber to wake up
        pthread_mutex_unlock(&mutex); // Release the mutex
        sem_wait(&barber); // Wait for the barber to be ready
        printf("[CUSTOMER %d] Getting haircut.\n", id); // Completion message
    } else {
        pthread_mutex_unlock(&mutex); // Release mutex if shop is full
        printf("[CUSTOMER %d] Leaving (Shop Full).\n", id); // Departure message
    }

    return NULL;
}

int main() {
    pthread_t barber_tid, customer_tid; // Thread identifiers
    sem_init(&customers, 0, 0); // Initialize customer semaphore to 0
    sem_init(&barber, 0, 0);    // Initialize barber semaphore to 0
    pthread_mutex_init(&mutex, NULL); // Initialize mutex for synchronization

    printf("--- STARTING DEADLOCK DEMONSTRATION ---\n");
    printf("The program will hang after the first customer arrives.\n\n");

    pthread_create(&barber_tid, NULL, barber_function, NULL); // Create Barber thread
    
    sleep(1); // Wait 1 second to ensure the Barber starts and grabs the mutex first
    
    int* id = malloc(sizeof(int)); // Allocate memory for Customer 1's ID
    *id = 1; // Set ID to 1
    pthread_create(&customer_tid, NULL, customer_function, id); // Create Customer thread

    /*
     * The program will now freeze. main() is waiting for customer_tid to finish,
     * but customer_tid is stuck waiting for a mutex that will never be released.
     */
    pthread_join(customer_tid, NULL); 
    
    return 0; // Return success (This line will never be reached)
}
