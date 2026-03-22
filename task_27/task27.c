#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * malicious shared library to hook the write() syscall.
 * This library intercepts write() calls and replaces "Hello, World!"
 * with "Goodbye, cruel world!".
 */

ssize_t write(int fd, const void *buf, size_t count) {
  // define a function pointer that matches the write() syscall signature
  ssize_t (*original_write)(int fd, const void *buf, size_t count);

  // initialize the pointer to the real write() function using dlsym
  original_write = dlsym(RTLD_NEXT, "write");

  // check if the buffer exactly matches "Hello, World!" (13 bytes)
  if (count >= 13 && strncmp((const char *)buf, "Hello, World!", 13) == 0) {
    // intercept and replace the message
    const char *new_message = "Goodbye, cruel world!";
    return original_write(fd, new_message, 21);
  }

  // otherwise, pass execution to the original write() syscall
  return original_write(fd, buf, count);
}
