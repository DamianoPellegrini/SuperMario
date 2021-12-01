# SuperMario

SuperMario clone written in C++20 using Vulkan 1.2.

## Build instructions

### Requirements

- premake5
- gmake

### Dependencies

- vulkan `1.2`
- xorg
- spirv tools

#### Linux

On Debian based systems, install the dependencies by using the following command:

```shell
apt install xorg-dev vulkan-tools libvulkan-dev spirv-tools
```

### Configure project

Run these command to get up and running

```shell
premake5 gmake
make clean
make config=release all
(cd ./run && exec ../bin/Release/SuperMario)
```
