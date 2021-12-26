# **SuperMario**

SuperMario clone written in C++20 using Vulkan.

## **Build instructions**

### Dependencies

- premake5
- VulkanSDK
- spirv tools
- xorg (on-linux)
- MoltenVK (on-macos)

#### *MacOS*

Install Xcode from the AppStore.
Install the **[VulkanSDK](https://vulkan.lunarg.com/sdk/home)**.
Install the remaning dependencies using **[homebrew](https://brew.sh/)**:

```shell
brew install --head premake \
&& brew install CocoaPods
```

#### *Linux*

On Debian based systems, install the dependencies by using the following command(you will need to prefix with sudo in most cases):

```shell
apt install \
    xorg-dev \
    vulkan-tools \
    libvulkan-dev \
    spirv-tools
```

### **Configure & Run**

Run these command to get up and running

```shell
premake5 gmake2
make clean
make config=release all
(cd ./run && exec ../bin/Release/SuperMario)
```
