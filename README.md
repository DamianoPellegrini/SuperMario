# SuperMario

SuperMario clone written in C++ using OpenGL 4.6 targetting mainly Linux-based operating systems.

## Build instructions

### Requirements (sources not included)

- premake5 `^alpha16`
- opengl `4.6`
- glfw `^3.3.4`
- cxxopts `^3.0.0`
- simdjson `^1.0.2`
- glm `0.9.9.8`
- gmake

#### Linux

On Debian based systems, install GLFW by using:

```shell
apt install libglfw3-dev
```

### Configure project

Start by generating the Makefile configuration using premake `premake5 gmake`

Next build the project, change the cwd and run it
```shell
make clean
make config=release all
cd ./run
../bin/Release/SuperMario
```
