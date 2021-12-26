project "SuperMario"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"

pchheader "pch.hpp"
pchsource "%{prj.location}/src/pch.cpp"

targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
objdir "%{wks.location}/obj/%{cfg.buildcfg}"

files {"%{prj.location}/src/**.cpp", "%{prj.location}/src/**.hpp"}

sysincludedirs {
    "%{prj.location}/src", "%{wks.location}/dependencies/glfw/include",
    "%{wks.location}/dependencies/spdlog/include",
    "%{wks.location}/dependencies/json/include",
    "%{wks.location}/dependencies/glm"
}

links {"glfw"}

filter "system:windows"
sysincludedirs {os.getenv("VULKAN_SDK") .. "/Include"}
libdirs {os.getenv("VULKAN_SDK") .. "/Lib"}
links {"vulkan-1"}

filter "system:linux"
buildoptions {"-Wvolatile"}
links {"vulkan", "dl", "pthread", "X11", "Xrandr", "Xxf86vm", "Xi"}

filter "system:macosx"
links {"Cocoa.framework", "IOKit.framework", "CoreVideo.framework", "vulkan"}
buildoptions {"-Wdeprecated-volatile", "-Wdeprecated-declarations"}

-- Cross platform dependencies
filter {}
