cmake_minimum_required(VERSION 3.15)
project(tglplus LANGUAGES CXX)

# Explicitly set Clang++ as the compiler
set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++")

# Use C++17 or later
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: enable warnings
# add_compile_options(-Wall -Wextra -Wpedantic)

# Optional: enable SIMD flags
# add_compile_options(-mavx512f -mavxvnni -mamx-int8)

# Add executable
add_executable(tglplus src/tglplus.cpp)
