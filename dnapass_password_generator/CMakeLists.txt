# CMake configuration for DNAPass Password Generator
cmake_minimum_required(VERSION 3.10)

# Add source files
set(SOURCE_FILES
    dnapass_generator.cpp
    main.cpp
)

# Add executable
add_executable(dnapass_generator ${SOURCE_FILES})

# Include header files
target_include_directories(dnapass_generator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
