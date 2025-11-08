This is a repository to hold Nokomis C and C++ assessment.

This is a monolithic repo and has both projects.
Prerequisite compilers are ```gcc``` and ```g++``` and can generally be found [here](https://sourceforge.net/projects/gcc-win64/).

```c test``` can be compiled with:

```console
gcc src/main.c -o main
./main
```

```cpptest``` can be compiled with:

```console
// I personally didn't have a dll installed for static libstdc++ so you can compile with
gcc src/main.c -o main -static -static-libstdc++
./main
```

Thanks for looking! Learned a ton just from this assignment. 
