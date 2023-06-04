# CMakeList.txt : CMake project for UTD, include source and define
# project specific logic here.
#

cmake_minimum_required(VERSION 3.21)

project(
    UTD
    VERSION 0.1
    DESCRIPTION "Unstandard Library"
    LANGUAGES CXX
)

# Libs
### Timer
add_library(timer SHARED)
set_target_properties(timer PROPERTIES CXX_STANDARD 20)
target_sources(timer PRIVATE src/utils/Timer.cpp)

### String
add_library(string SHARED)
set_target_properties(string PROPERTIES CXX_STANDARD 20)
target_sources(string PRIVATE src/data-structures/String.cpp)

# Test 
enable_testing()
add_executable (UTD_test)
set_property(TARGET UTD_test PROPERTY CXX_STANDARD 20)
target_sources(UTD_test PRIVATE tests/main.cpp)
target_link_libraries(UTD_test PRIVATE timer string)
add_test(NAME Test_1 COMMAND UTD_test)

# Build 
add_executable (UTD)
set_property(TARGET UTD PROPERTY CXX_STANDARD 20)
target_sources(UTD PRIVATE src/demo/Demo.cpp src/demo/main.cpp) 
target_link_libraries(UTD PRIVATE timer string)
