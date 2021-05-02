workspace "SuperMario"
    configurations { "Debug", "Profile", "Release" }
    -- platforms { "Windows", "Linux" }
    -- architecture "x86_64"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    
    filter {}

project "SuperMario"
    location "SuperMario"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    
    pchheader "pch.hpp"
    pchsource "SuperMario/src/pch.cpp"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    files {
        "SuperMario/src/**.cpp",
        "SuperMario/src/**.hpp"
    }

    includedirs {
        "SuperMario/src"
    }

    links {
        "GL",
        "glfw"
    }