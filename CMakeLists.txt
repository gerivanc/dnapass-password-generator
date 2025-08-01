# CMakeLists.txt
# DNAPass Password Generator - CMake Configuration
#
# Project Name: DNAPass Password Generator
# Version: 0.1.1
# Description: Generate secure passwords inspired by DNA sequences written in C++.
# Author: Gerivan Costa dos Santos <dean-grumbly-plop@duck.com>
# License: MIT License
# Homepage: https://github.com/gerivanc/dnapass-password-generator
# Repository: https://github.com/gerivanc/dnapass-password-generator.git
# Issues: https://github.com/gerivanc/dnapass-password-generator/issues
# Changelog: https://github.com/gerivanc/dnapass-password-generator/blob/main/CHANGELOG.md

cmake_minimum_required(VERSION 3.10)
project(DNAPass VERSION 0.1.1 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add source files
set(SOURCE_FILES
    dnapass_password_generator/dnapass_generator.cpp
    dnapass_password_generator/main.cpp
)

# Add executable
add_executable(dnapass_generator ${SOURCE_FILES})

# Include header files
target_include_directories(dnapass_generator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dnapass_password_generator)

# Installation rules (optional, for installing the executable)
install(TARGETS dnapass_generator DESTINATION bin)

# Add custom message for build completion
add_custom_command(TARGET dnapass_generator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "DNAPass Password Generator v0.1.1 built successfully!"
)
