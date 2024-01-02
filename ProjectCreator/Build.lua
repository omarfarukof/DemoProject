-- MainApp
workspace "ProjectCreator"
    configurations { "Debug", "Release", "Dist" , "Publish"}
    architecture "x64"

    startproject "ProjectCreator"

    OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
    LibRelativeDir = "../../"

-- Include Libs
group "Libs"
    include "libs/CppProject/Build-CppProject.lua"
    -- include "libs/lib2/Build-lib2.lua"

    -- include "libs/CppProject/Build-CppProject.lua"
group ""

-- Main App
project "ProjectCreator"
    kind "ConsoleApp"
    language "C++"
    targetdir ( "bin/" .. OutputDir )
    objdir ( "bin/Intermediates/" .. OutputDir )

    files { "app/include/**.h", "app/src/**.cpp" }

    includedirs {
        "app/include",
        "libs/CppProject/include",
        -- "libs/lib2/include",
    }

    -- links {  }  -- Add this line to link against CppProject, Lib2, and Mylib
    links {
        "CppProject",
    }

    filter "configurations:Publish"
        defines { "PUBLISH" }
        targetdir "../Scripts/"