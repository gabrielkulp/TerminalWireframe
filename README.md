# Wireframe 3D Text Graphics Engine
Made by Gabriel Kulp as a personal side project through 2018 and 2019.

## How do I run it?
First, you'll need something UNIX-like with a C compiler (`gcc` by default, optionally `clang` or `tcc`), the `tput` command, `make`, and optionally `valgrind`. This probably limits you to some flavor of Linux or BSD.

To compile and run, type `make run`. Press ctrl+c to exit. You can also see line count statistics with `make stats`, delete build files with `make clean`, and check for memory leaks with `make mem` (assuming you have `valgrind` installed).

If you want to try some other compiler, change line 1 of the Makefile. On my system, running `gcc` with -O3 (possibly-standards-breaking optimizations) does not break anything. If you see memory leaks or any other issues, feel free to change line 4 of the Makefile to use -O2 or -O1 to prevent these issues.


## What features are planned?
* Import standard 3D model formats like STL
* Limit the framerate so small terminals don't run faster
* Optimize flushing buffers so it doesn't take so many IO operations
* Add some easy way to read keys to allow interactiveness
* Add structs for a scene hierarchy with multiple objects
* Abstract coordinates one more time to allow moving the camera
