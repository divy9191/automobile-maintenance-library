cmake_minimum_required(VERSION 3.16)
project(AutomobileMaintenanceLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows-specific configuration
if(WIN32)
    # Prefer MinGW or MSYS2 over Visual Studio for simpler builds
    if(NOT DEFINED CMAKE_GENERATOR)
        set(CMAKE_GENERATOR "MinGW Makefiles" CACHE STRING "Build system generator" FORCE)
    endif()
    
    # Set compiler flags for Windows
    if(MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    endif()
endif()

# Find required packages
find_package(PkgConfig REQUIRED)

# Add executable
add_executable(maintenance_server
    src/Automobile.cpp
    src/MaintenanceTask.cpp
    src/MaintenanceLibrary.cpp
    src/main.cpp
)

# Include directories
target_include_directories(maintenance_server PRIVATE src)

# Link libraries - cross-platform threading
if(WIN32)
    # Windows uses native threading, no need for pthread
    if(MINGW)
        target_link_libraries(maintenance_server pthread)
    endif()
else()
    # Unix-like systems use pthread
    target_link_libraries(maintenance_server pthread)
endif()

# Compiler flags - cross-platform
if(MSVC)
    # Visual Studio compiler flags
    target_compile_options(maintenance_server PRIVATE /W4 /O2)
else()
    # GCC/Clang flags (including MinGW)
    target_compile_options(maintenance_server PRIVATE -Wall -Wextra -O2)
endif()

# Tests (optional, uncomment if Google Test is available)
# find_package(GTest REQUIRED)
# add_executable(run_tests
#     tests/test_automobile.cpp
#     tests/test_maintenance_library.cpp
#     src/Automobile.cpp
#     src/MaintenanceTask.cpp
#     src/MaintenanceLibrary.cpp
# )
# target_include_directories(run_tests PRIVATE src)
# target_link_libraries(run_tests GTest::gtest GTest::gtest_main pthread)
