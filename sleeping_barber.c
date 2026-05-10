#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define CHAIRS 5           // Number of chairs in the waiting room
#define TOTAL_CUSTOMERS 10 // Total number of customers to simulate

// Semaphores and Mutex
sem_t customers;       // Number of customers waiting for service
sem_t barber;          // Number of barbers waiting for customers
pthread_mutex_t mutex; // For mutual exclusion when accessing 'waiting' count

int waiting = 0; // Number of customers currently in the waiting room

// Function for the Barber thread
void *barber_function(void *arg) {
  while (1) {
    // Wait for a customer to arrive (Barber sleeps if no customers)
    sem_wait(&customers);

    // Lock mutex to update the count of waiting customers
    pthread_mutex_lock(&mutex);
    waiting--; // Customer moves from waiting room to barber chair

    // Signal the barber is ready to cut hair
    sem_post(&barber);

    // Unlock mutex
    pthread_mutex_unlock(&mutex);

    // Cutting hair (simulated by sleep)
    printf("Barber: Cutting hair. Customers waiting: %d\n", waiting);
    fflush(stdout);
    sleep(2);
  }
  return NULL;
}

// Function for the Customer threads
void *customer_function(void *arg) {
  int id = *(int *)arg;
  free(arg);

  // Lock mutex to check if there's a free chair
  pthread_mutex_lock(&mutex);

  if (waiting < CHAIRS) {
    waiting++; // Customer takes a seat
    printf("Customer %d: Entering shop. Waiting customers: %d\n", id, waiting);
    fflush(stdout);

    // Notify the barber that a customer is ready
    sem_post(&customers);

    // Unlock mutex so other customers can check chairs
    pthread_mutex_unlock(&mutex);

    // Wait for the barber to be free
    sem_wait(&barber);
    printf("Customer %d: Getting a haircut.\n", id);
    fflush(stdout);
  } else {
    // No free chairs, customer leaves
    pthread_mutex_unlock(&mutex);
    printf("Customer %d: Shop full. Leaving.\n", id);
    fflush(stdout);
  }

  return NULL;
}

int main() {
  pthread_t barber_tid;
  pthread_t customer_tids[TOTAL_CUSTOMERS];

  // Initialize Semaphores and Mutex
  sem_init(&customers, 0, 0); // Initially 0 customers
  sem_init(&barber, 0, 0);    // Initially barber is not ready
  pthread_mutex_init(&mutex, NULL);

  // Create Barber thread
  pthread_create(&barber_tid, NULL, barber_function, NULL);

  // Create Customer threads at random intervals
  for (int i = 0; i < TOTAL_CUSTOMERS; i++) {
    int *id = malloc(sizeof(int));
    *id = i + 1;
    pthread_create(&customer_tids[i], NULL, customer_function, id);

    // Random delay between customer arrivals
    usleep(rand() % 1000000);
  }

  // Wait for all customer threads to finish
  for (int i = 0; i < TOTAL_CUSTOMERS; i++) {
    pthread_join(customer_tids[i], NULL);
  }

  printf("All customers served or left. Simulation finished.\n");
  fflush(stdout);

  return 0;
}
