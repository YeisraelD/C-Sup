## 24

so now, going to build a C program that executes syscalls! i think, i've already learned basically everything i need to know in C up until this point to accomplish this. im going to keep it simple and to use the open() syscall only here. It should be noted that technically im not making syscalls directly in user programs, but instead are using wrapper functions defined in libc for my purposes.

the first thing is that, the unistd.h header file contains all the syscall wrapper functions i need and fcntl.h contains file control functions. so to include those is must.

The `open()` syscall wrapper can take a third argument when the `O_CREAT` flag is used. This argument specifies the file permissions for the new file. Constants like `S_IRWXU` (User Read-Write-Execute) are defined in `<sys/stat.h>`, making it another essential header.

```c
filedescriptor = open("testfile.txt", O_WRONLY | O_CREAT, S_IRWXU);
```

On success, `open()` returns a file descriptor (a non-negative integer). On failure, it returns -1.

Output:
```terminal_session
The open operation succeeded!
```

