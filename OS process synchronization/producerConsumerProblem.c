#include <stdio.h>
#define N 100
int count = 0;

void producer(void){
    int item;

    while (TRUE){
        item = producer_item();  // generate the item, whatever kind of data it is
        if(count == N) sleep() // buffer is full so sleep
        insert_item(item);    //add item
        count = count + 1; // item count up
        if (count == 1 ) wakeup(consumer); // buffer was empty , so notify consumer

    }
}

void consumer(void){
    int item;

    while (TRUE){
        if(count == 0) sleep(); //go bed there is nothing to take
        item = remove_item();
        count = count -1 ;// count one down
        if(count == N-1) wakeup(producer);
        consumer_item(item);

    }
}