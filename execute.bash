#!/bin/bash

# Globbing all .c, .cpp, .h, and .hpp files
files=$(find . -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \))

# Print the files
for file in $files; 
do
    echo "$file"
done

g++ -std=c++11 -o main $files
chmod +x main
./main