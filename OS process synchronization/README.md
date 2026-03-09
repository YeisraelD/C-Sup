When the consumer wants to remove an item from the buffer and sees that the buffer is empty, it goes to sleep until the producer puts something in the buffer and wakes it up. If it is nonzero, remove an item and decrement count.


but this classic problem has a race condition, which is a lost wakeup problem
```terminal_session
consumer checks count == 0
before calling sleep() producer adds
producer calls wakeup(consumer)
but consumer wasnt asleep yet
wakeup is lost -> consumer sleeps forever, lucky right
```
in modern os instead of sleep()/ wakeup() we use mutex , semaphores, and condition variables, this guarante atomic operations.

[producer consumer problem solution with semaphores](https://github.com/YeisraelD/C-Sup/blob/main/OS%20process%20synchronization/prodConsProb_semaphores.c)

so synchronization primitives prevent these race conditions

but, even also on the semaphore solution there is an other problem.

"deadlock"
init
```terminal_session
mutex	1	critical section free
empty	0	no empty slots
full	N	buffer full
```

producer runs

```terminal_session
down(mutex)
down(empty)
```

Producer enters critical section. then producer blocks (sleeps) waiting for an empty slot. Producer is still holding the mutex lock.

consumer runs
```terminal_session
down(mutex)
```

Consumer cannot get mutex.

Producer cannot release mutex because it is blocked.

kinda both lost
but most os`s just ignore this condition.

not sure with what mechanism we fix this ....
