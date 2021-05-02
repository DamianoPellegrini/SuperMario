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
    
    -- Deactivate filtering
    filter {}

    -- Adding every dependency that need to be compiled
    group "Dependencies"
        include "dependencies/glad"

    group ""
        include "SuperMario"
