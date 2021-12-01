workspace "SuperMario"
configurations {"Debug", "Profile", "Release"}
vectorextensions "SSE2"
flags {"MultiProcessorCompile", "LinkTimeOptimization"}
-- architecture "x86_64"

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

filter "system:macosx"
system "macosx"

-- Deactivate filtering
filter {}

-- Adding every dependency that need to be compiled
group "Dependencies"
include "dependencies/glfw.lua"
include "dependencies/spdlog.lua"

group ""
include "SuperMario"
