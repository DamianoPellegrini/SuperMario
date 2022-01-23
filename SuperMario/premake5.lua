project "SuperMario"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    pchheader "pch.hpp"
    pchsource "%{prj.location}/src/pch.cpp"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}"

    files {"%{prj.location}/src/**.cpp", "%{prj.location}/src/**.hpp"}

    includedirs {"%{prj.location}/src"}

    sysincludedirs {
        "%{wks.location}/dependencies/glfw/include",
        "%{wks.location}/dependencies/glad/include",
        "%{wks.location}/dependencies/spdlog/include",
        "%{wks.location}/dependencies/json/include",
        "%{wks.location}/dependencies/glm"
    }

    links {"glfw"}

    filter "system:windows"
        targetname "%{prj.name}.exe"
        sysincludedirs {os.getenv("VULKAN_SDK") .. "/Include"}
        libdirs {os.getenv("VULKAN_SDK") .. "/Lib"}
        links {"vulkan-1"}

    filter "system:linux"
        targetname "%{prj.name}"
        buildoptions {"-Wvolatile"}
        links {"vulkan", "dl", "pthread", "X11", "Xrandr", "Xxf86vm", "Xi"}

    filter "system:macosx"
        targetname "%{prj.name}.app"
        links {
            "Cocoa.framework", "IOKit.framework", "CoreVideo.framework",
            "vulkan"
        }
        buildoptions {"-Wdeprecated-volatile", "-Wno-deprecated-declarations", "-Wno-defaulted-function-deleted"}

    -- Cross platform dependencies
    filter {}
        postbuildcommands {
            "{COPY} %{wks.location}/run/** %{cfg.targetdir}"
        }