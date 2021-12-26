workspace "SuperMario"
configurations {"Debug", "Profile", "Release"}
vectorextensions "SSE2"
architecture "x86_64"
flags {"MultiProcessorCompile"}

filter "configurations:Debug"
defines {"DEBUG"}
runtime "Debug"
symbols "On"

filter "configurations:Release"
defines {"NDEBUG"}
runtime "Release"
optimize "On"

filter "system:windows"
system "windows"

filter "system:linux"
system "linux"
flags {"LinkTimeOptimization"}

filter "system:macosx"
system "macosx"

-- Deactivate filtering
filter {}

-- Adding every dependency that need to be compiled
group "Dependencies"
include "dependencies/glfw.lua"

group ""
include "SuperMario"
