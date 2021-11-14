# SuperMario

SuperMario clone written in C++20 using OpenGL 4.6 targetting mainly Linux-based operating systems.

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

On Debian based systems, install the dependencies by using the following command:

```shell
apt install libglfw3-dev libsimdjson-dev libglm-dev
```

### Configure project

Run these command to get up and running

```shell
premake5 gmake
make clean
make config=release all
(cd ./run && exec ../bin/Release/SuperMario)
```
