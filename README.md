# dengine

dengine is intended to be a simple 2D, sprite/tile based game engine.
It is being created by a person that knows nothing about video game creation, video game design, or even much in the 
way of C++ development. It is purely being built as a learning exercise. Anyone that's looking for a real engine should
 probably take a look at something like Unity.
 
# Build

The build system generated using cmake.

## Linux

First, make sure you have the following installed:

- [Simple DirectMedia Layer 2](http://libsdl.org/)
- [SDL_Image](https://www.libsdl.org/projects/SDL_image/)
- CMake >= 3.5
- gcc / clang compiler
- libzip and header (e.g. `apt-get install libzip libzip-dev`)
- zlib and headers (e.g. `apt-get install zlib zlib-dev`)

For example on Ubunut 16.04:

```commandline
sudo apt-get install build-essential libsdl2-dev libsdl2-image-dev
```

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
cd examples/asteroids
./asteroids
```

## Mac OS (10.12, but probably works on earlier versions)

First, make sure you have the following installed:

- [Simple DirectMedia Layer 2](http://libsdl.org/)
- [SDL_Image](https://www.libsdl.org/projects/SDL_image/)
- CMake >= 3.5
- XCode

For example on macOS 10.12 with Homebrew:

```commandline
brew install cmake sdl2 sdl2_image
```

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
cd examples/asteroids
./asteroids
```
