#include <unistd.h>

/**
 * Test program for Task 27.
 * This program writes "Hello, World!" to stdout.
 * When run with LD_PRELOAD=./task27.so, the output should be hooked.
 */

int main(void)
{
    write(1, "Hello, World!", 13);
    write(1, "\n", 1);
    return 0;
}
