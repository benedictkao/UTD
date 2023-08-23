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

##include_directories("${PROJECT_SOURCE_DIR}")

# Libs
### Timer
add_library(timer SHARED)
set_target_properties(timer PROPERTIES CXX_STANDARD 20)
target_sources(timer PRIVATE "src/utils/timer.cpp")

### Math
add_library(math SHARED)
set_target_properties(math PROPERTIES CXX_STANDARD 20)
target_sources(math PRIVATE "src/utils/math.cpp")

### Functional
add_library(functional SHARED)
set_target_properties(functional PROPERTIES CXX_STANDARD 20)
target_sources(functional PRIVATE "src/utils/hash.cpp")

# Build 
add_executable(main)
set_property(TARGET main PROPERTY CXX_STANDARD 20)
target_sources(main PRIVATE "src/demo/demo.cpp" "src/demo/main.cpp")
target_link_libraries(main PRIVATE
    timer
    functional
)

# Test
enable_testing()
add_executable (main_test)
set_property(TARGET main_test PROPERTY CXX_STANDARD 20)
target_sources(main_test PRIVATE
    "tests/main.cpp"
    "tests/data-structures/vector_test.cpp"
    "tests/data-structures/string32_test.cpp"
    "tests/data-structures/array_test.cpp"
    "tests/data-structures/unordered_set_test.cpp"
    "tests/utils/hash_test.cpp"
)
target_link_libraries(main_test
    gtest_main
    math
    functional
)

add_test(NAME main COMMAND main_test)

# G Tests
include(GoogleTest)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/be03d00f5f0cc3a997d1a368bee8a1fe93651f48.zip
)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.2) # need master for benchmark::benchmark

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest googlebenchmark)

add_executable(vector_test "tests/data-structures/vector_test.cpp")
set_property(TARGET vector_test PROPERTY CXX_STANDARD 20)
target_link_libraries(vector_test gtest_main math)

add_executable(string32_test "tests/data-structures/string32_test.cpp")
set_property(TARGET string32_test PROPERTY CXX_STANDARD 20)
target_link_libraries(string32_test
    gtest_main
)

add_executable(array_test "tests/data-structures/array_test.cpp")
set_property(TARGET array_test PROPERTY CXX_STANDARD 20)
target_link_libraries(array_test gtest_main)

add_executable(unordered_set_test "tests/data-structures/unordered_set_test.cpp")
set_property(TARGET unordered_set_test PROPERTY CXX_STANDARD 20)
target_link_libraries(unordered_set_test gtest_main functional)

gtest_discover_tests(vector_test string32_test array_test unordered_set_test)

# Benchmark
add_library(benchmark_helper SHARED)
set_target_properties(benchmark_helper PROPERTIES CXX_STANDARD 20)
target_link_libraries(benchmark_helper benchmark::benchmark)
target_sources(benchmark_helper PRIVATE "benchmarks/helper.cpp")

add_executable(main_string_benchmark "benchmarks/string.cpp")
set_property(TARGET main_string_benchmark PROPERTY CXX_STANDARD 20)
target_link_libraries(main_string_benchmark
    benchmark::benchmark
    benchmark_helper
)

add_executable(main_vector_benchmark "benchmarks/vector.cpp")
set_property(TARGET main_vector_benchmark PROPERTY CXX_STANDARD 20)
target_link_libraries(main_vector_benchmark benchmark::benchmark math benchmark_helper)
