# CMake configuration for DNAPass Password Generator
cmake_minimum_required(VERSION 3.10)

project(DNAPass VERSION 0.1.0 LANGUAGES CXX)

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

# Installation rules
install(TARGETS dnapass_generator DESTINATION bin)

# Add custom message for build completion
add_custom_command(TARGET dnapass_generator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "DNAPass Password Generator v0.1.0 built successfully!"
)
