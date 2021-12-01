project "spdlog"
location "spdlog"
kind "StaticLib"
language "C++"
cppdialect "C++20"

targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
objdir "%{wks.location}/obj/%{cfg.buildcfg}"

files {"%{prj.location}/src/**.cpp", "%{prj.location}/include/spdlog/**.h"}

includedirs {"%{prj.location}/include"}

defines {"SPDLOG_COMPILED_LIB"}

filter "system:windows"

filter "system:linux"

-- Cross platform dependencies
filter {}
