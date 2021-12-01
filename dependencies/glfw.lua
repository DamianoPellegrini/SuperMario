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
    "%{prj.location}/src/xkb_unicode.c", "%{prj.location}/src/xkb_unicode.h",
    "%{prj.location}/src/egl_context.c", "%{prj.location}/src/egl_context.h",
    "%{prj.location}/src/osmesa_context.c",
    "%{prj.location}/src/osmesa_context.h", "%{prj.location}/include/**.h"
}

includedirs {"%{prj.location}/include"}

-- defines {"_GLFW_VULKAN_STATIC"}

-- platform specific
filter "system:windows"
files {
    "%{prj.location}/src/wgl_context.c", "%{prj.location}/src/wgl_context.h",
    "%{prj.location}/src/win32_init.c", "%{prj.location}/src/win32_joystick.c",
    "%{prj.location}/src/win32_joystick.h",
    "%{prj.location}/src/win32_monitor.c",
    "%{prj.location}/src/win32_platform.h",
    "%{prj.location}/src/win32_thread.c", "%{prj.location}/src/win32_time.c",
    "%{prj.location}/src/win32_window.c"
}
includedirs {os.getenv("VULKAN_SDK") .. "/Include"}
libdirs {os.getenv("VULKAN_SDK") .. "/Lib"}
defines {"_GLFW_WIN32", "_CRT_SECURE_NO_WARNINGS"}

filter "system:linux"
files {
    "%{prj.location}/src/linux_joystick.c",
    "%{prj.location}/src/linux_joystick.h",

    "%{prj.location}/src/posix_thread.c", "%{prj.location}/src/posix_thread.h",
    "%{prj.location}/src/posix_time.c", "%{prj.location}/src/posix_time.h",
    -- _GLFW_OSMESA
    -- "%{prj.location}/src/null_init.c",
    -- "%{prj.location}/src/null_monitor.c",
    -- "%{prj.location}/src/null_platform.h",
    -- "%{prj.location}/src/null_window.c",
    -- "%{prj.location}/src/null_joystick.c",
    -- "%{prj.location}/src/null_joystick.h",
    -- _GLFW_X11
    "%{prj.location}/src/glx_context.h", "%{prj.location}/src/glx_context.c",
    "%{prj.location}/src/x11_init.c", "%{prj.location}/src/x11_monitor.c",
    "%{prj.location}/src/x11_platform.h", "%{prj.location}/src/x11_window.c"
    -- _GLFW_WAYLAND
    -- "%{prj.location}/src/wl_init.c",
    -- "%{prj.location}/src/wl_monitor.c",
    -- "%{prj.location}/src/wl_platform.h",
    -- "%{prj.location}/src/wl_window.c",
}
defines {"_GLFW_X11"}
-- defines {"_GLFW_OSMESA"}
-- defines {"_GLFW_WAYLAND"}

filter "system:macosx"
files {
    "%{prj.location}/src/nsgl_context.c", "%{prj.location}/src/nsgl_context.h",
    "%{prj.location}/src/cocoa_init.m", "%{prj.location}/src/cocoa_joystick.m",
    "%{prj.location}/src/cocoa_joystick.h",
    "%{prj.location}/src/cocoa_monitor.m",
    "%{prj.location}/src/cocoa_platform.h", "%{prj.location}/src/cocoa_time.c",
    "%{prj.location}/src/cocoa_window.c"
}
defines {"_GLFW_COCOA"}

filter {}
