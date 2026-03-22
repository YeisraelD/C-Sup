Now that I've successfully used syscalls and I know how to parse arguments with some research, let's move onto something a little bit more complicated but still very doable. I'm going to create a C program that binds a command shell to a listening port, also known as a **bind shell** (in TCP!).

I'm going to tell you the syscalls I need to make in order to accomplish this and also try and drop some hints about potential sticking points. I won't be fully walking through this one like our previous exercise, but as always there will be a solution made available should you get stuck (`task26.c`).

## Resources
A good resource throughout this exercise will be the socket programming tutorial here: [Socket Programming Tutorial](http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html). Keep referencing this document for every parameter and every function.

Another great resource is [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/multi/index.html).

### Header Files
I'm going to need to include the following header files:

```c
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
```
Pull these header files up and read through them; learn what they're for and why we need them. You should be finding man pages for all of these syscalls and reading about their parameters and definitions.

## Syscalls
### Socket()
The first syscall I'm going to make is `socket()`. The explanation for socket is not very difficult. Make sure you pay attention to the return value, as this value will be needed for subsequent syscalls.

### Bind()
The next syscall will be `bind()`. This one is a bit of a challenge, so I will help you with it. The function definition for `bind` is: `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`. I can get the `sockfd` parameter from my `socket()` call.

Next, I need to build a struct. The struct definition I'll be using is `sockaddr_in`. This is because `bind()` takes an argument that is a pointer to a struct of type `sockaddr`; however, I actually use `sockaddr_in` as our struct type because they are the same size and, according to the manpage for `bind`, "the only purpose of `sockaddr` is to cast the structure pointer passed in `addr` in order to avoid compiler warnings."

I first need to create an instance of the `sockaddr_in` struct called `server_addr`:

```c
struct sockaddr_in server_addr;
```

Next, start assigning values to the members of this struct. The relevant members are:
- `sin_family`
- `sin_port`
- `sin_addr`

`sin_family` can take values defined inside of `<sys/socket.h>`. Since I'm creating a TCP bind shell, I'll need to use the `AF_INET` value (for IPv4). So I can assign it with: `server_addr.sin_family = AF_INET;`.

Next, I need to set `sin_addr`. The `sin_addr` member is actually of type `struct in_addr`. The `struct in_addr` contains only one member: an `unsigned long s_addr`.

```c
struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr below
    char             sin_zero[8];  // padding
};

struct in_addr {
    unsigned long s_addr;          // load with INADDR_ANY or inet_aton()
};
```

To set the value of the `sin_addr` member: `server_addr.sin_addr.s_addr = <insert value>;`.

Wait, what does `sin_addr` do? It specifies the address of the machine I want to listen on (the server). According to the IP manpage: "When `INADDR_ANY` is specified in the bind call, the socket will be bound to all local interfaces." For my bind shell, I'll use `INADDR_ANY`: `server_addr.sin_addr.s_addr = INADDR_ANY;`.

The last member of my struct is `sin_port`. I need to use the `htons()` function to convert my port value to network byte order: `server_addr.sin_port = htons(5555);`.

Altogether, my bind call should look like: `bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));`.

### Listen()
This syscall is straightforward. For the backlog, you can specify `0`.

### Accept()
For this syscall, read the description here: [Accept Syscall Details](https://www.geeksforgeeks.org/accept-system-call/). For this exercise, I can use `NULL` for the 2nd and 3rd arguments. Pay close attention to the return value; it will be used in subsequent calls.

### Dup2()
What `dup2()` does is take an old file descriptor (returned from my `accept()` syscall) and duplicates it to `stdin`, `stdout`, and `stderr`. These three file descriptors have values of 0, 1, and 2 respectively. Call `dup2()` three times to copy the client file descriptor to these three new ones. (Extra credit: implement this with a `for` loop.)

### Execve()
This is my last syscall. I want to execute `/bin/sh` so that my client can have a shell. This syscall can be called with the name of the program you want executed and two `NULL` arguments.

If this is your first time working with sockets, you will probably spend a lot of time researching – that is perfectly fine and intended. Don't get frustrated! As a last resort, check the solution (`task26.c`).

**Extra Credit:** Add error checking to your program!