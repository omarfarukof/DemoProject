#!/bin/bash

# Source the function file
source lua_build_functions.sh

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
