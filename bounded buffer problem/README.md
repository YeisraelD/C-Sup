When the consumer wants to remove an item from the buffer and sees that the buffer is empty, it goes to sleep until the producer puts something in the buffer and wakes it up. If it is nonzero, remove an item and decrement count.


but this classic problem has a race condition, which is a lost wakeup problem
```terminal_session
consumer checks count == 0
before calling sleep() producer adds
producer calls wakeup(consumer)
but consumer wasnt asleep yet
wakeup is lost -> consumer sleeps forever, lucky right
```