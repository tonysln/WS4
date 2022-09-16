# WS4

C++ 20

libsfml-dev >= 2.6.0

gcc 11+

cmake 3+

OpenGL ?

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
- Finish Extended Forecast graphics
- Add Air Quality colors
- Create Air Quality graphics
- Add shadow toggle/info to text in data file
- Music playback loop
- Timers for changing screens
- Pretty much all of data gathering stuff