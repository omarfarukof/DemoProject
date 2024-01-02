#!/bin/bash

# Create project directories
mkdir -p libs/lib1/include/lib1 libs/lib1/src libs/lib2/include/lib2 libs/lib2/src app/include/app app/src

# Create example files
touch premake5.lua
touch libs/lib1/include/lib1/lib1.h
touch libs/lib1/src/lib1.cpp
touch libs/lib2/include/lib2/lib2.h
touch libs/lib2/src/lib2.cpp
touch app/include/app/main.h
touch app/src/main.cpp

# Output success message
echo "Project structure created successfully."
