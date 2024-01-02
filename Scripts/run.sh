#!/bin/bash

# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Source the function file
# source lua_build_functions.sh
# Function to generate the Lua code based on the given arguments
generate_lua_code_staticlib() {
    local directory_name=$1

    cat << EOF
--${directory_name}
project "${directory_name}"

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
EOF
}


# Function to generate the Lua code based on the given arguments
generate_lua_code_MainBuild() {
    local directory=$1

    # Capture the output of ls in a variable
    local build_lib_path=$(ls $directory/libs/*/*.lua)

    # Loop through the items in the build_lib_path variable
    local IFS=$'\n'  # Set Internal Field Separator to newline to handle filenames with spaces

    local lib_include_path=$(find $directory/libs -type d -name "include")

    echo -e "-- MainApp
workspace \"MyCppProject\"
    configurations { \"Debug\", \"Release\", \"Dist\" }
    architecture \"x64\"

    startproject \"MainApp\"

    OutputDir = \"%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}\"
    LibRelativeDir = \"../../\"

-- Include Libs
group \"Libs\""
    for item in $build_lib_path; do
        echo "    include "\"${item/$directory\//}"\""
    done
    echo -e "
    -- include \"libs/lib1/Build-lib1.lua\"
group \"\"

-- Main App
project \"MainApp\"
    kind \"ConsoleApp\"
    language \"C++\"
    targetdir ( \"bin/\" .. OutputDir )
    objdir ( \"bin/Intermediates/\" .. OutputDir )

    files { \"app/include/**.h\", \"app/src/**.cpp\" }
"
    echo "    includedirs {"
    echo "        \"app/include\","
    for item in $lib_include_path; do
        echo "        "\"${item/$directory\//}"\","
    done 
    echo "    }"

    echo -e "
    -- links {  }  -- Add this line to link against Lib1, Lib2, and Mylib"
    echo "    links {"
    for item in $build_lib_path; do
        project_name=$(sed -n 's/project "\(.*\)"/\1/p' "$item")
        echo "        "\"${project_name}"\","
    done
    echo "    }"


# Reset IFS to its default value
    unset IFS
}



# ================================================================================

# Check if the --staticlib argument is provided
if [ "$1" = "--luastaticlib" ]; then
    # Assume the directory name is the second argument
    directory=${2:-./}

    # Check if the directory name is provided
    if [ "$(basename "$directory")" = "." ]; then
        # echo "Usage: $0 --staticlib <directory-name>"
        # exit 1
        directory_name="$(basename $(pwd))"

    else
        directory_name="$(basename "$directory")"
    fi



    # Call the function from the sourced file
    generate_lua_code_staticlib "$directory_name" > "$directory/Build-$directory_name.lua"
    echo "Generated:  Build-$directory_name.lua"


elif [ "$1" = "--luamainbuild" ]; then
    # Assume the directory name is the second argument
    directory=${2:-./}



    # Call the function from the sourced file
    generate_lua_code_MainBuild "$directory" > "$directory/Build.lua"
    echo "Generated:  Build.lua"

elif [ "$1" = "--build" ]; then
    source Setup-Linux.sh $2

elif [ "$1" = "--make" ]; then
    pushd $2
    make $3
    popd

elif [ "$1" = "--run" ]; then
    pushd $2
    "bin/linux-x86_64/Release/MainApp"
    # popd

elif [ "$1" = "--cmd" ]; then
    # --mainbuild provided
    # Add code for the main build here
    echo "Performing cmd..."
    # Add your build commands as needed
    # For example: make

else
    echo "Usage: $0 --staticlib <directory-name>"
    exit 1
fi
