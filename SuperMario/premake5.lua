project "SuperMario"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"

pchheader "pch.hpp"
pchsource "%{prj.location}/src/pch.cpp"

targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
objdir "%{wks.location}/obj/%{cfg.buildcfg}"

files {"%{prj.location}/src/**.cpp", "%{prj.location}/src/**.hpp"}

includedirs {
    "%{prj.location}/src", "%{wks.location}/dependencies/glfw/include",
    "%{wks.location}/dependencies/spdlog/include",
    "%{wks.location}/dependencies/json/include",
    "%{wks.location}/dependencies/glm"
}

buildoptions {"-Wvolatile"}
links {"glfw", "spdlog"}

filter "system:windows"
links {"vulkan"}

filter "system:linux"
links {"vulkan", "dl", "pthread", "X11", "Xrandr", "Xxf86vm", "Xi"}

-- Cross platform dependencies
filter {}
