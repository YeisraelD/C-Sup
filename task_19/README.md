## 19\
Initialize a char pointer variable. Use the malloc() function to allocate memory for a char array by assigning the result of malloc() to the pointer. the program should check that the memory was indeed allocated and if not, print an error message and exit with code 1. Make sure the allocation size is a multiple of the char data type by using the sizeof() function so the code is portable. Google best practices for using malloc(). Don't forget to use free() to free the memory space before exiting the program if successful.

Print a success or failure message to the terminal.
```terminal_session
IEngine-Pid-qqihkv51.hpk --dbgExe=C:\msys64\ucrt64\bin\gdb.exe --interpreter=mi "
Memory was successfully allocated.
```