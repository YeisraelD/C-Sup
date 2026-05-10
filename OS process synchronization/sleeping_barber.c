#include <pthread.h>   // Library for POSIX thread creation and management
#include <semaphore.h> // Library for semaphore synchronization primitives
#include <stdio.h>     // Standard I/O library for printing output
#include <stdlib.h>    // Standard library for memory allocation (malloc/free)
#include <unistd.h>    // Unix standard header for sleep and usleep functions

#define CHAIRS 5           // Macro defining the maximum capacity of the waiting room chairs
#define TOTAL_CUSTOMERS 10 // Macro defining how many customer threads the simulation will create

sem_t customers; // Counting semaphore to track the number of customers waiting for service
sem_t barber;    // Binary semaphore to track whether the barber is ready to start a haircut
pthread_mutex_t mutex; // Mutex to ensure mutual exclusion when accessing the shared 'waiting' variable

int waiting = 0; // Shared integer variable representing the current number of customers in the waiting room

// Function executed by the Barber thread
void *barber_function(void *arg) {
  while (1) { // Infinite loop representing the barber's continuous workday
    sem_wait(&customers); // Blocking operation: Barber sleeps if no customers are available (semaphore count 0)

    pthread_mutex_lock(&mutex); // Entry Section: Acquire lock to safely modify the shared 'waiting' count

    waiting--; // Critical Section: Decrease the count as one customer moves from a chair to the barber's seat

    sem_post(&barber); // Signaling: Notify the customer thread that the barber is now ready for them

    pthread_mutex_unlock(&mutex); // Exit Section: Release the lock so other threads can access the 'waiting' variable

    printf("[BARBER] Processing service. Remaining in waiting room: %d\n", waiting); // Log status to console
    fflush(stdout); // Ensure the output buffer is cleared and text is immediately visible
    sleep(2); // Simulate the time-consuming task of cutting hair (2 seconds)
  }
  return NULL; // Return NULL (required by thread function signature)
}

// Function executed by each Customer thread
void *customer_function(void *arg) {
  int id = *(int *)arg; // Retrieve the unique ID assigned to this specific customer thread
  free(arg); // Free the memory allocated in main for passing the ID

  pthread_mutex_lock(&mutex); // Entry Section: Acquire lock to check the shared state of the waiting room

  if (waiting < CHAIRS) { // Condition Check: Verify if there is at least one empty chair available
    waiting++; // Critical Section: Increment the count as the customer successfully takes a seat
    printf("[CUSTOMER %d] Entered shop. Current occupancy: %d\n", id, waiting); // Log entry status
    fflush(stdout); // Force immediate output to the terminal

    sem_post(&customers); // Signaling: Increment customer semaphore to wake the barber if he is sleeping

    pthread_mutex_unlock(&mutex); // Exit Section: Release the lock to allow other customers to check the chairs

    sem_wait(&barber); // Blocking: Wait for the barber to signal that it is this customer's turn
    printf("[CUSTOMER %d] Thread now receiving service.\n", id); // Log that service has started
    fflush(stdout); // Clear output buffer
  } else { // Handle case where all chairs are occupied
    pthread_mutex_unlock(&mutex); // Exit Section: Release lock before leaving to avoid deadlocking others
    printf("[CUSTOMER %d] Shop capacity reached. Thread terminating (Leaving).\n", id); // Log departure
    fflush(stdout); // Clear output buffer
  }

  return NULL; // Customer thread finishes its task and exits
}

int main() {
  pthread_t barber_tid; // Variable to store the thread identifier for the barber
  pthread_t customer_tids[TOTAL_CUSTOMERS]; // Array to store identifiers for all customer threads

  sem_init(&customers, 0, 0); // Initialize customer semaphore to 0 (initially no customers)
  sem_init(&barber, 0, 0);    // Initialize barber semaphore to 0 (initially barber is idle)
  pthread_mutex_init(&mutex, NULL); // Initialize the mutex with default attributes

  printf("--- INITIALIZING SLEEPING BARBER SIMULATION ---\n"); // Print header
  printf("Waiting Room Capacity: %d chairs\n\n", CHAIRS); // Print configuration details

  pthread_create(&barber_tid, NULL, barber_function, NULL); // Launch the Barber thread

  for (int i = 0; i < TOTAL_CUSTOMERS; i++) { // Loop to create the specified number of customers
    int *id = malloc(sizeof(int)); // Dynamically allocate memory for the customer's unique ID
    *id = i + 1; // Assign ID value (1 to 10)
    pthread_create(&customer_tids[i], NULL, customer_function, id); // Launch a new Customer thread

    usleep(rand() % 1000000); // Wait for a random period (up to 1 second) before next customer arrives
  }

  for (int i = 0; i < TOTAL_CUSTOMERS; i++) { // Loop to ensure the main thread waits for all customers
    pthread_join(customer_tids[i], NULL); // Wait for customer thread 'i' to finish before proceeding
  }

  printf("\n--- SIMULATION COMPLETE: All threads processed ---\n"); // Final termination message
  fflush(stdout); // Ensure final output is printed

  return 0; // Return 0 to indicate successful program completion
}
