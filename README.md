# C Renderer

A simple 3d renderer made in C. It uses low level libraries such as SDL and OpenGL to handle things such as input handling, window opening and other OS reliant functionalities.

### What can it do?

It is very basic, it can render primitive shapes, like triangles and cubes, handle shaders, VBOs and IBOs and also handle perspective & orthogonal cameras.

This program also has some general purpuse functionalities like a frame rate counter, timers and input handling functions.

### How do I run it?

This program was only compiled to linux with gcc, at the moment, but, due to libraries such as SDL it can run on Windows and MacOS.

Independently of what OS you are using, you have to compile it by yourself.
If you are using the gcc compiler and already have SDL2 installed globaly in your machine you can use the makefile
that is already in the source code, you just need to run the following command at the source code directory:
```
make
```
after the code has been compiled and linked, you may run the executable binary.
