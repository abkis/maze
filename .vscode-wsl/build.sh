#!/bin/bash

# Ensure workspaceFolder is set, either from an environment variable or manually
if [ -z "$workspaceFolder" ]; then
    workspaceFolder=$(pwd)  # Default to the current directory if not set
fi

# Find all include directories in the 'headers' folder
INCLUDE_DIRS=$(find ${workspaceFolder}/headers -type d -exec echo -I{} \;)

# Find all source files in the 'src' folder
SOURCE_FILES=$(find ${workspaceFolder}/src -name "*.cpp")

# Compile the program with g++
g++ -std=c++17 ${workspaceFolder}/main.cpp $SOURCE_FILES $INCLUDE_DIRS -o ${workspaceFolder}/main -lsfml-graphics -lsfml-window -lsfml-system
