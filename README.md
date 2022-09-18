# WS4

C++ 20

libsfml-dev >= 2.6.0

gcc 11+

cmake 3+

OpenGL ?

OpenAL ?

### Build

Make sure that the correct path is set in the Makefile for SFML files.

```bash
$ cd src
$ make clean
$ make
```

### Run

```bash
$ export LD_LIBRARY_PATH=<path to /lib> && ./WS4
```

### TODOs

- Read in icons, create textures & sprites (re-use objs?)
- Pressure up/down arrows on CC screen
- Music playback loop fix
- Pretty much all of data gathering stuff