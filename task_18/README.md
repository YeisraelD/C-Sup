%s expects a C string, and a C string must end with '\0'.

Since my array does not contain '\0', printf will keep reading memory past the array until it randomly finds a '\0'.

That means:

It might print correctly by luck

It might print garbage characters

It might crash

This is undefined behavior.

If you print with:
```terminal_session
%s
```
the data must end with '\0'.

Otherwise, wil print undefined behavior

first file
```terminal_session
IEngine-Pid-bfipwukh.s44 --dbgExe=C:\msys64\ucrt64\bin\gdb.exe --interpreter=mi "
Hello, World!��_
```

second
```terminal_session
Hello, World!
```