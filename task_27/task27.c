#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>

/**
 * Task 27: malicious shared library to hook the write() syscall.
 * This library intercepts write() calls and replaces "Hello, World!"
 * with "Goodbye, cruel world!".
 */

ssize_t write(int fd, const void *buf, size_t count)
{
    // Define a function pointer that matches the write() syscall signature
    ssize_t (*original_write)(int fd, const void *buf, size_t count);

    // Initialize the pointer to the real write() function using dlsym
    original_write = dlsym(RTLD_NEXT, "write");

    // Check if the buffer exactly matches "Hello, World!" (13 bytes)
    if (count >= 13 && strncmp((const char *)buf, "Hello, World!", 13) == 0)
    {
        // Intercept and replace the message
        const char *new_message = "Goodbye, cruel world!";
        return original_write(fd, new_message, 21);
    }

    // Otherwise, pass execution to the original write() syscall
    return original_write(fd, buf, count);
}
