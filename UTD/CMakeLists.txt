# CMakeList.txt : CMake project for UTD, include source and define
# project specific logic here.
#

cmake_minimum_required(VERSION 3.15)

# set(CMAKE_C_COMPILER gcc-12)
# set(CMAKE_CXX_COMPILER g++-12)

project(
    UTD
    VERSION 0.1
    DESCRIPTION "Unstandard Library"
    LANGUAGES CXX
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Libs
### Timer
add_library(timer SHARED)
set_target_properties(timer PROPERTIES CXX_STANDARD 20)
target_sources(timer PRIVATE src/utils/Timer.cpp)

### String
add_library(string SHARED)
set_target_properties(string PROPERTIES CXX_STANDARD 20)
target_sources(string PRIVATE src/data-structures/String.cpp src/data-structures/String32.cpp)

# Build 
add_executable (UTD)
set_property(TARGET UTD PROPERTY CXX_STANDARD 20)
target_sources(UTD PRIVATE src/demo/Demo.cpp src/demo/main.cpp) 
target_link_libraries(UTD PRIVATE timer string)

# Test 
enable_testing()
add_executable (UTD_test)
set_property(TARGET UTD_test PROPERTY CXX_STANDARD 20)
target_sources(UTD_test PRIVATE tests/main.cpp)
target_link_libraries(UTD_test PRIVATE timer string)
add_test(NAME Test_1 COMMAND UTD_test)

# G Tests
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/be03d00f5f0cc3a997d1a368bee8a1fe93651f48.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
add_executable(vector_tests tests/vector_tests/vector_tests.cpp)
set_property(TARGET vector_tests PROPERTY CXX_STANDARD 20)
target_link_libraries(vector_tests gtest_main)
gtest_discover_tests(vector_tests)
