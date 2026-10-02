# CMakeLists.txt
# DNAPass Password Generator - CMake Configuration
#
# Project Name: DNAPass Password Generator
# Version: 0.1.5
# Description: Generate secure passwords inspired by DNA sequences written in C++.
# Author: Gerivan Costa dos Santos <dean-grumbly-plop@duck.com>
# License: MIT License
# Homepage: https://github.com/gerivanc/dnapass-password-generator
# Repository: https://github.com/gerivanc/dnapass-password-generator.git
# Issues: https://github.com/gerivanc/dnapass-password-generator/issues
# Changelog: https://github.com/gerivanc/dnapass-password-generator/blob/main/CHANGELOG.md

cmake_minimum_required(VERSION 3.10)
project(DNAPass VERSION 0.1.5 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(DNAPASS_BUILD_TESTS "Build the DNAPass automated tests" ON)

# Core library: password generation + OS CSPRNG
add_library(dnapass_core STATIC
    dnapass_password_generator/dnapass_generator.cpp
    dnapass_password_generator/secure_random.cpp
)
target_include_directories(dnapass_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dnapass_password_generator)

# Windows: BCryptGenRandom lives in bcrypt.lib / libbcrypt.a
if(WIN32)
    target_link_libraries(dnapass_core PUBLIC bcrypt)
endif()

# Command-line executable
add_executable(dnapass_generator dnapass_password_generator/main.cpp)
target_link_libraries(dnapass_generator PRIVATE dnapass_core)

# Set compiler-specific flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(dnapass_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(dnapass_generator PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Installation rules
install(TARGETS dnapass_generator DESTINATION bin)

# Add custom message for build completion
add_custom_command(TARGET dnapass_generator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "DNAPass Password Generator v${PROJECT_VERSION} built successfully!"
)

# Automated tests (run with: ctest --output-on-failure)
if(DNAPASS_BUILD_TESTS)
    enable_testing()

    add_executable(dnapass_tests tests/test_generator.cpp)
    target_link_libraries(dnapass_tests PRIVATE dnapass_core)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(dnapass_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    add_test(NAME generator_policy COMMAND dnapass_tests)
    add_test(NAME cli_version COMMAND dnapass_generator --version)
    add_test(NAME cli_length_quiet COMMAND dnapass_generator --length 12 --quiet)
    add_test(NAME cli_all_toggles COMMAND dnapass_generator -l 64 --no-uppercase --no-digits)
    add_test(NAME cli_rejects_short_length COMMAND dnapass_generator --length 7)
    set_tests_properties(cli_rejects_short_length PROPERTIES WILL_FAIL TRUE)
endif()
