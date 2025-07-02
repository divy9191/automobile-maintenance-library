cmake_minimum_required(VERSION 3.16)
project(AutomobileMaintenanceLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Link libraries
target_link_libraries(maintenance_server pthread)

# Compiler flags
target_compile_options(maintenance_server PRIVATE -Wall -Wextra -O2)

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
