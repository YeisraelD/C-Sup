Now that I've got some more syscall experience under my belt, I'm going to take a step back and actually look at how syscalls are implemented. I'm going to create a malicious shared library to hook some syscalls. I am getting very naughty.

I will be using these excellent blog posts as my guides: [Ketan Singh: Overview on Linux Userland Rootkits](https://ketansingh.net/overview-on-linux-userland-rootkits/) and [NetSPI: Function Hooking Part I](https://blog.netspi.com/function-hooking-part-i-hooking-shared-library-function-calls-in-linux/). I recommend reading through these posts at least twice.

## Shared Libraries
A shared library is essentially a compiled `.c` file that contains definitions of functions. These files typically end with the extension `.so`. When you run a dynamically linked binary and it makes a `write()` syscall for instance, it seeks out the definition for `write()` in a shared library file called `libc`. As far as the binary knows, `write()` means whatever `libc` says it means. Normally, this is a good thing. Instead of having to recompile all binaries when a function is altered in a shared library, users can instead just update the shared library and have all of its dependent binaries across the system work as intended.

I can see what shared libraries are consulted by a binary with the `ldd` utility which checks for dynamic dependencies. Let's see which shared libraries `ls` uses on a Kali Linux installation:

```terminal_session
$ ldd /bin/ls
	linux-gate.so.1 (0xb7f54000)
	libselinux.so.1 => /lib/i386-linux-gnu/libselinux.so.1 (0xb7ed7000)
	libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xb7cf9000)
	libdl.so.2 => /lib/i386-linux-gnu/libdl.so.2 (0xb7cf3000)
	libpcre.so.3 => /lib/i386-linux-gnu/libpcre.so.3 (0xb7c7a000)
	/lib/ld-linux.so.2 (0xb7f56000)
	libpthread.so.0 => /lib/i386-linux-gnu/libpthread.so.0 (0xb7c59000)
```

I see a reference to `libc.so.6` and see that it's located at `/lib/i386-linux-gnu/libc.so.6`. I recommend you read more about shared libraries, dynamic linking/loading, and static linking. There's a ton of useful information there for noobs like me.

What I'm after, is finding out what order the dynamic linker finds and loads shared libraries needed by a program. According to the `ld.so` manpage, the order is:

1. Using the directories specified in the `DT_RPATH` dynamic section attribute of the binary if present and `DT_RUNPATH` attribute does not exist.
2. Using the environment variable `LD_LIBRARY_PATH`, unless the executable is being run in secure-execution mode.
3. Using the directories specified in the `DT_RUNPATH` dynamic section attribute of the binary if present.
4. From the cache file `/etc/ld.so.cache`.
5. In the default path `/lib`, and then `/usr/lib`.

Or, as they put it on the Ketan Singh blogpost: "directories listed in the `LD_LIBRARY_PATH` environment variable, directories listed in the executable’s rpath, and directories on the system search path."

I can also see in the `ld.so` manpage that there is an option for an `LD_PRELOAD` environment variable which will always be sought first. Outside of declaring an environment variable, I can also use the `/etc/ld.so.preload` file to list the file path of a `.so` to load first.

## So, What?
Well, if I can have a binary reference a malicious shared library instead of the legitimate shared library, I could have the binary behave in a way that is beneficial to me and potentially invisible to the end user. What if, for example, I redefined the `write()` syscall in a malicious shared library so that when it's invoked, it silently sends a copy of its write buffer to a file somewhere and then continues a normal write operation? The end user of the binary invoking `write()` would have no idea their content was being copied.

This technique is one way in which it's possible to hook syscalls. The advantage of using `LD_PRELOAD` instead of specifying an `.so` in the `/etc/ld.so.preload` file is that with the environment variable, you can specify a specific binary for which it applies.

## Getting Evil
In the NetSPI blog post, they hook the `puts()` syscall with the following malicious shared library:

```c
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>

int puts(const char *message) {
    int (*new_puts)(const char *message);
    int result;
    new_puts = dlsym(RTLD_NEXT, "puts");
    
    if (strcmp(message, "Hello world!\n") == 0) {
        result = new_puts("Goodbye, cruel world!\n");
    } else {
        result = new_puts(message);
    }
    return result;
}
```

Analysis:
- `int puts(const char *message)` matches the real `puts` function signature.
- `int (*new_puts)(const char *message)` is a pointer that will point to the legitimate `puts()` call.
- `new_puts = dlsym(RTLD_NEXT, "puts")` initializes the pointer to the "next" instance of `puts` in the library search path (the real one).
- `if (strcmp(message, "Hello world!\n") == 0)` intercepts the specific string and replaces it.

So if this shared library is loaded, the binary will change the message "Hello world!" to "Goodbye, cruel world!".

