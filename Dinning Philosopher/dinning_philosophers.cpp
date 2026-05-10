#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = {0, 1, 2, 3, 4};
sem_t mutex;
sem_t S[N];

void test(int phnum) {
  if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
    state[phnum] = EATING;
    sleep(1);
    printf("[SIM] Philosopher %d acquired forks %d & %d. State: EATING\n", phnum + 1, LEFT + 1, phnum + 1);
    fflush(stdout);
    sem_post(&S[phnum]);
  }
}

void take_fork(int phnum) {
  sem_wait(&mutex);
  state[phnum] = HUNGRY;
  printf("[SIM] Philosopher %d is HUNGRY\n", phnum + 1);
  fflush(stdout);
  test(phnum);
  sem_post(&mutex);
  sem_wait(&S[phnum]);
}

void put_fork(int phnum) {
  sem_wait(&mutex);
  state[phnum] = THINKING;
  printf("[SIM] Philosopher %d released forks. State: THINKING\n", phnum + 1);
  fflush(stdout);
  test(LEFT);
  test(RIGHT);
  sem_post(&mutex);
}

void *philosopher(void *num) {
  int id = *(int *)num;
  while (1) {
    sleep(1);
    take_fork(id);
    sleep(1);
    put_fork(id);
  }
}

int main() {
  pthread_t thread_id[N];
  sem_init(&mutex, 0, 1);
  for (int i = 0; i < N; i++) {
    sem_init(&S[i], 0, 0);
  }
  printf("====================================================\n");
  printf("   DINING PHILOSOPHERS SYNCHRONIZATION SIMULATOR    \n");
  printf("====================================================\n\n");
  for (int i = 0; i < N; i++) {
    pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
  }
  for (int i = 0; i < N; i++) {
    pthread_join(thread_id[i], NULL);
  }
  return 0;
}
