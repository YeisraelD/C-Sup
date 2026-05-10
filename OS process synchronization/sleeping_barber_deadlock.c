#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define CHAIRS 5
#define TOTAL_CUSTOMERS 5

sem_t customers;
sem_t barber;
pthread_mutex_t mutex;
int waiting = 0;

void* barber_function(void* arg) {
    while (1) {
        printf("[BARBER] Attempting to lock mutex...\n");
        pthread_mutex_lock(&mutex);
        printf("[BARBER] Mutex locked. Now waiting for a customer (This will cause DEADLOCK)...\n");
        fflush(stdout);
        sem_wait(&customers);
        waiting--;
        sem_post(&barber);
        pthread_mutex_unlock(&mutex);
        printf("[BARBER] Cutting hair...\n");
        sleep(2);
    }
    return NULL;
}

void* customer_function(void* arg) {
    int id = *(int*)arg;
    free(arg);
    printf("[CUSTOMER %d] Arrived. Trying to lock mutex to check for chairs...\n", id);
    fflush(stdout);
    pthread_mutex_lock(&mutex);
    if (waiting < CHAIRS) {
        waiting++;
        printf("[CUSTOMER %d] Entering shop...\n", id);
        sem_post(&customers);
        pthread_mutex_unlock(&mutex);
        sem_wait(&barber);
        printf("[CUSTOMER %d] Getting haircut.\n", id);
    } else {
        pthread_mutex_unlock(&mutex);
        printf("[CUSTOMER %d] Leaving (Shop Full).\n", id);
    }
    return NULL;
}

int main() {
    pthread_t barber_tid, customer_tid;
    sem_init(&customers, 0, 0);
    sem_init(&barber, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    printf("--- STARTING DEADLOCK DEMONSTRATION ---\n");
    printf("The program will hang after the first customer arrives.\n\n");
    pthread_create(&barber_tid, NULL, barber_function, NULL);
    sleep(1);
    int* id = malloc(sizeof(int));
    *id = 1;
    pthread_create(&customer_tid, NULL, customer_function, id);
    pthread_join(customer_tid, NULL);
    return 0;
}
