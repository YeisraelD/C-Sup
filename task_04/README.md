## 4
Prompt the user to input the length of a radius and then print the area of the user's circle to the terminal.

here note 2 things, first the #define feature of C to assign the value 3.14 to PIE, is just text replacement, literally the processor will PIE with 3.14 before compilation.

the second one is that, scanf() need a memory address not a value
if u just miss &, you would be passing a value to scanf(), which is garbage at first, or like some sort of undefined behavior.

but c++ uses references internally, it handles the address automatically
c is much low-level, we manage the memory manually.

```terminal_session
4\ucrt64\bin\gdb.exe --interpreter=mi "
enter the radius of ur circle: 12
the area of ur circle is:452 
```
