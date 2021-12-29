project "glad"
    location "glad"
    kind "StaticLib"
    language "C"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}"

    files {
        "%{prj.location}/src/**.c",
        "%{prj.location}/include/**.h",
    }

    includedirs {"%{prj.location}/include"}
