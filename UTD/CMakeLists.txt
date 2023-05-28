# CMakeList.txt : CMake project for UTD, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (UTD "src/demo/Demo.cpp" "src/demo/main.cpp"  "src/utils/Timer.cpp" "src/data-structures/string/String.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET UTD PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
