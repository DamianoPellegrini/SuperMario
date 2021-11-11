project "SuperMario"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    
    pchheader "pch.hpp"
    pchsource "%{prj.location}/src/pch.cpp"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}"

    files {
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/**.hpp"
    }

    includedirs {
        "%{prj.location}/src",
        "%{wks.location}/dependencies/glad/include"
    }

    links {
        "GL",
        "glfw",
        "glad",
        "simdjson",
        "dl",
        "pthread",
    }
