# DNAPass Password Generator - CMake Configuration
#
# Project Name: DNAPass Password Generator
# Version: 0.1.0
# Description: Generate secure passwords inspired by DNA sequences written in C++.
# Author: Gerivan Costa dos Santos <dean-grumbly-plop@duck.com>
# License: MIT License
# Homepage: https://github.com/gerivanc/dnapass
# Repository: https://github.com/gerivanc/dnapass.git
# Issues: https://github.com/gerivanc/dnapass/issues
# Changelog: https://github.com/gerivanc/dnapass/blob/main/CHANGELOG.md

cmake_minimum_required(VERSION 3.10)
project(DNAPass VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable
add_executable(dnapass_generator dnapass_generator.cpp)

# Specify include directories (none needed for standard libraries)
# target_include_directories(dnapass_generator PRIVATE ${CMAKE_SOURCE_DIR})

# Specify no external dependencies, as only standard C++ libraries are used
# target_link_libraries(dnapass_generator PRIVATE <library>)

# Installation rules (optional, for installing the executable)
install(TARGETS dnapass_generator DESTINATION bin)

# Add custom message for build completion
add_custom_command(TARGET dnapass_generator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "DNAPass Password Generator v0.1.0 built successfully!"
)
