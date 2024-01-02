-- CppProject
project "CppProject"

    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ( LibRelativeDir .. "bin/" .. OutputDir .. "/%{prj.name}")
    objdir ( LibRelativeDir .. "bin/Intermediates/" .. OutputDir .. "/%{prj.name}")

    files { "include/**.h", "src/**.cpp" }
    includedirs { "include" }

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
