#define _GNU_SOURCE
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(void) {
  const char *msg1 = "1. High-level: printf() called.\n";
  const char *msg2 = "2. Mid-level:  write() (libc wrapper) called.\n";
  const char *msg3 = "3. Low-level:  syscall() (manual passing) called.\n";

  // Level 1: High-level Library Function
  // This eventually calls the write() syscall internally.
  printf("%s", msg1);

  // Level 2: Standard C Library Wrapper
  // This is the direct POSIX wrapper for the kernel's write syscall.
  write(1, msg2, 46);

  // Level 3: Manual Syscall Parameter Passing
  // Here, we explicitly tell the library to execute 'SYS_write' (1).
  // The 'syscall()' function takes the ID and the raw arguments
  // and places them into the CPU registers (rax, rdi, rsi, rdx).
  syscall(SYS_write, 1, msg3, 50);

  return 0;
}
