# CMakeLists.txt
# DNAPass Password Generator - CMake Configuration
#
# Project Name: DNAPass Password Generator
# Version: 0.1.2
# Description: Generate secure passwords inspired by DNA sequences written in C++.
# Author: Gerivan Costa dos Santos <dean-grumbly-plop@duck.com>
# License: MIT License
# Homepage: https://github.com/gerivanc/dnapass-password-generator
# Repository: https://github.com/gerivanc/dnapass-password-generator.git
# Issues: https://github.com/gerivanc/dnapass-password-generator/issues
# Changelog: https://github.com/gerivanc/dnapass-password-generator/blob/main/CHANGELOG.md

cmake_minimum_required(VERSION 3.10)
project(DNAPass VERSION 0.1.2 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add source files - CORRETO: arquivos estão na pasta dnapass_password_generator
set(SOURCE_FILES
    dnapass_password_generator/dnapass_generator.cpp
    dnapass_password_generator/main.cpp
)

# Add executable
add_executable(dnapass_generator ${SOURCE_FILES})

# Include header files - CORRETO: headers estão na pasta dnapass_password_generator
target_include_directories(dnapass_generator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dnapass_password_generator)

# Set compiler-specific flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(dnapass_generator PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Installation rules (optional)
install(TARGETS dnapass_generator DESTINATION bin)

# Add custom message for build completion
add_custom_command(TARGET dnapass_generator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "DNAPass Password Generator v${PROJECT_VERSION} built successfully!"
)
