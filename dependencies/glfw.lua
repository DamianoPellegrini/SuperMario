project "glfw"
    location "glfw"
    kind "StaticLib"
    language "C"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}"

    files {
        "%{prj.location}/src/context.c", "%{prj.location}/src/init.c",
        "%{prj.location}/src/input.c", "%{prj.location}/src/internal.h",
        "%{prj.location}/src/mappings.h", "%{prj.location}/src/monitor.c",
        "%{prj.location}/src/vulkan.c", "%{prj.location}/src/window.c",
        "%{prj.location}/include/**.h", "%{prj.location}/src/glfw_config.h",
    }

    includedirs {"%{prj.location}/include"}

    defines {"_GLFW_VULKAN_STATIC"} -- Require the loader to be linked when compiling glfw

    -- platform specific
    filter "system:windows"
        files {
            "%{prj.location}/src/wgl_context.c", "%{prj.location}/src/wgl_context.h",
            "%{prj.location}/src/egl_context.h", "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c", "%{prj.location}/src/osmesa_context.h",
            "%{prj.location}/src/win32_init.c", "%{prj.location}/src/win32_joystick.c",
            "%{prj.location}/src/win32_joystick.h",
            "%{prj.location}/src/win32_monitor.c",
            "%{prj.location}/src/win32_platform.h",
            "%{prj.location}/src/win32_thread.c", "%{prj.location}/src/win32_time.c",
            "%{prj.location}/src/win32_window.c"
        }
        sysincludedirs {os.getenv("VULKAN_SDK") .. "/Include"}
        libdirs {os.getenv("VULKAN_SDK") .. "/Lib"}
        defines {"_GLFW_WIN32", "_CRT_SECURE_NO_WARNINGS"}
        links {"vulkan-1"}

    filter "system:linux"
        files {
            "%{prj.location}/src/linux_joystick.c",
            "%{prj.location}/src/linux_joystick.h",

            "%{prj.location}/src/posix_thread.c", "%{prj.location}/src/posix_thread.h",
            "%{prj.location}/src/posix_time.c", "%{prj.location}/src/posix_time.h",
            "%{prj.location}/src/glx_context.h", "%{prj.location}/src/glx_context.c",
            "%{prj.location}/src/egl_context.h", "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c", "%{prj.location}/src/osmesa_context.h",
            "%{prj.location}/src/x11_init.c", "%{prj.location}/src/x11_monitor.c",
            "%{prj.location}/src/x11_platform.h", "%{prj.location}/src/x11_window.c",
            "%{prj.location}/src/xkb_unicode.c", "%{prj.location}/src/xkb_unicode.h"
        }
        defines {"_GLFW_X11"}

    filter "system:macosx"
        files {
            "%{prj.location}/src/nsgl_context.m", "%{prj.location}/src/nsgl_context.h",
            "%{prj.location}/src/cocoa_init.m", "%{prj.location}/src/cocoa_joystick.m",
            "%{prj.location}/src/cocoa_joystick.h",
            "%{prj.location}/src/cocoa_monitor.m",
            "%{prj.location}/src/posix_thread.c", "%{prj.location}/src/posix_thread.h",
            "%{prj.location}/src/egl_context.h", "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.h", "%{prj.location}/src/osmesa_context.c",
            "%{prj.location}/src/cocoa_platform.h", "%{prj.location}/src/cocoa_time.c",
            "%{prj.location}/src/cocoa_window.m"
        }
        defines {"_GLFW_COCOA"}

    filter {}
