# dengine

dengine is intended to be a simple 2D, sprite/tile based game engine.
It is being created by a person that knows nothing about video game creation, video game design, or even much in the 
way of C++ development. It is purely being built as a learning exercise. Anyone that's looking for a real engine should
 probably take a look at something like Unity.
 
# Build

Builds are generated using cmake. The only target OS that will be tested against will be Ubuntu 16.04. The steps to
build the engine and examples are as follows.

First, make sure you have the following installed:

- [Simple DirectMedia Layer 2](http://libsdl.org/)
- [SDL_Image](https://www.libsdl.org/projects/SDL_image/)
- CMake >= 3.5
- gcc / clang compiler

Next, generate a make file:

```commandline
mkdir -p build
cd build
cmake ../
```

Next, run the makefile generated for you system:

```commandline
make
```

You should now be able to run one of the example applications:

```commandline
./examples/asteroids
```
