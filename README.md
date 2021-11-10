# SuperMario

SuperMario clone written in C++ using OpenGL 4.6 targetting mainly Linux-based operating systems.

## Build instructions

### Requirements

- premake5
- gmake

### Dependencies

- opengl `4.6`
- glfw `^3.3.4`
- simdjson `^1.0.2`
- glm `^0.9.9.8`

#### Linux

On Debian based systems, install the dependencies by using:

```shell
apt install libglfw3-dev libsimdjson-dev libglm-dev
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
