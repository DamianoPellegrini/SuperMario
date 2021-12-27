workspace "SuperMario"
configurations {"Debug", "Profile", "Release"}
-- architecture "x86_64"
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
vectorextensions "SSE2"

filter "system:linux"
system "linux"
vectorextensions "SSE2"
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
