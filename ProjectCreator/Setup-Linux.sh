#!/bin/bash

# Run Premake command with the specified target
$1/Vendor/Binaries/Premake/Linux/premake5 --cc=gcc --file=$1/Build.lua gmake2

# # pushd ..
# # Vendor/Binaries/Premake/Linux/premake5 --cc=gcc --file=Build.lua gmake2 
# Vendor/Binaries/Premake/Linux/premake5 --cc=gcc --file=Build.lua $1
# # popd
