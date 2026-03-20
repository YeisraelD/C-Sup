## 24

so now, going to build a C program that executes syscalls! i think, i've already learned basically everything i need to know in C up until this point to accomplish this. im going to keep it simple and to use the open() syscall only here. It should be noted that technically im not making syscalls directly in user programs, but instead are using wrapper functions defined in libc for my purposes.

the first thing is that, the unistd.h header file contains all the syscall wrapper functions i need and fcntl.h contains file control functions. so to include those is must.
