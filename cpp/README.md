```terminal_session
 ___________________________________________
/ "C++ is the best example of second-system \
| effect since OS/360."                      |
\__________________________________________ /  
   \           .  . .   `  ,
    \       .; . : .' :  :  : .
     \      i..\ `: i` i.i.,i  i .
      \    `,--.|i |i|ii|ii|i:
            UooU\.'@@@@@@`.||'
            \__/(@@@@@@@@@@)'
                  (@@@@@@@@)
                  `YY~~~~YY'
                    ||   ||
```

Low level C++

no fancy frameworks.  
no hand holding abstractions.  
Just structs, pointers, manual memory, bit twiddling, and occasional segfaults.

### Tech stack (if you can call it that)

- C++ (probably C++11/14, whatever allowed)
- gcc / clang
- valgrind (highly recommended)
- prayer

### Build & run (example, adapt per lab)

```bash
cd Lab3b
g++ -Wall -Wextra -g -o main *.cpp
valgrind --leak-check=full ./main
