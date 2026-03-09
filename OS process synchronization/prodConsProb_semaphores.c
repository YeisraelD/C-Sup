#include <stdio.h>
#define N 100
typedef int semaphore;
semaphore mutex = 1;
semaphore full = 0;
semaphore empty = N;

void producer(void){
    int item;

    while (true){
        item = producer_item();    // creat item 
        down(&empty);      // wait for empty slot , if ibuffer is full producer waits automatically
        down(&mutex);    // enter critical section, lock
        insert_item(item);
        up(&mutex);     //unlock, leave cs
        up(&full);     // ++ count of full slot , this signals the consumer that an item exists

    }
}

void consumer(void){
    int item;

    while (true){
        down(&full); // wait for an item
        down(&mutex); // enter cs
        item = remove_item();
        up(&mutex);  // leave cs
        up(&empty); // increase empty slot
        conusme_item(item); // use the data

    }
}
