#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CHAIRS 5
#define TOTAL_CUSTOMERS 10

sem_t customers;
sem_t barber;
pthread_mutex_t mutex;

int waiting = 0;

void *barber_function(void *arg) {
  while (1) {
    sem_wait(&customers);
    pthread_mutex_lock(&mutex);
    waiting--;
    sem_post(&barber);
    pthread_mutex_unlock(&mutex);
    printf("[BARBER] Processing service. Remaining in waiting room: %d\n", waiting);
    fflush(stdout);
    sleep(2);
  }
  return NULL;
}

void *customer_function(void *arg) {
  int id = *(int *)arg;
  free(arg);
  pthread_mutex_lock(&mutex);
  if (waiting < CHAIRS) {
    waiting++;
    printf("[CUSTOMER %d] Entered shop. Current occupancy: %d\n", id, waiting);
    fflush(stdout);
    sem_post(&customers);
    pthread_mutex_unlock(&mutex);
    sem_wait(&barber);
    printf("[CUSTOMER %d] Thread now receiving service.\n", id);
    fflush(stdout);
  } else {
    pthread_mutex_unlock(&mutex);
    printf("[CUSTOMER %d] Shop capacity reached. Thread terminating (Leaving).\n", id);
    fflush(stdout);
  }
  return NULL;
}

int main() {
  pthread_t barber_tid;
  pthread_t customer_tids[TOTAL_CUSTOMERS];
  sem_init(&customers, 0, 0);
  sem_init(&barber, 0, 0);
  pthread_mutex_init(&mutex, NULL);
  printf("--- INITIALIZING SLEEPING BARBER SIMULATION ---\n");
  printf("Waiting Room Capacity: %d chairs\n\n", CHAIRS);
  pthread_create(&barber_tid, NULL, barber_function, NULL);
  for (int i = 0; i < TOTAL_CUSTOMERS; i++) {
    int *id = malloc(sizeof(int));
    *id = i + 1;
    pthread_create(&customer_tids[i], NULL, customer_function, id);
    usleep(rand() % 1000000);
  }
  for (int i = 0; i < TOTAL_CUSTOMERS; i++) {
    pthread_join(customer_tids[i], NULL);
  }
  printf("\n--- SIMULATION COMPLETE: All threads processed ---\n");
  fflush(stdout);
  return 0;
}
