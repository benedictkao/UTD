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
target_sources(timer PRIVATE "src/utils/timer.cpp")

### String
add_library(string SHARED)
set_target_properties(string PROPERTIES CXX_STANDARD 20)
target_sources(string PRIVATE "src/data-structures/string32.cpp")

### Math
add_library(math SHARED)
set_target_properties(math PROPERTIES CXX_STANDARD 20)
target_sources(math PRIVATE "src/utils/math.cpp")

# Build 
add_executable(main)
set_property(TARGET main PROPERTY CXX_STANDARD 20)
target_sources(main PRIVATE "src/demo/demo.cpp" "src/demo/main.cpp") 
target_link_libraries(main PRIVATE timer string)

# Test
enable_testing()
add_executable (main_test)
set_property(TARGET main_test PROPERTY CXX_STANDARD 20)
target_sources(main_test PRIVATE "tests/main.cpp" "tests/data-structures/vector_test.cpp" "tests/data-structures/string32_test.cpp")
target_link_libraries(main_test gtest_main math string)

add_test(NAME main COMMAND main_test)

# G Tests
include(GoogleTest)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/be03d00f5f0cc3a997d1a368bee8a1fe93651f48.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(vector_test "tests/data-structures/vector_test.cpp")
set_property(TARGET vector_test PROPERTY CXX_STANDARD 20)
target_link_libraries(vector_test gtest_main math)

add_executable(string32_test "tests/data-structures/string32_test.cpp")
set_property(TARGET string32_test PROPERTY CXX_STANDARD 20)
target_link_libraries(string32_test gtest_main string)

gtest_discover_tests(vector_test string32_test)
