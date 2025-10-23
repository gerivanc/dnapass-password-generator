cmake_minimum_required(VERSION 3.10)
project(DNAPass VERSION 0.1.2 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add source files
set(SOURCE_FILES
    dnapass_generator.cpp
    main.cpp
)

# Add executable
add_executable(dnapass_generator ${SOURCE_FILES})

# Set compiler-specific flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(dnapass_generator PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Add custom message for build completion
add_custom_command(TARGET dnapass_generator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "DNAPass Password Generator v${PROJECT_VERSION} built successfully!"
)
