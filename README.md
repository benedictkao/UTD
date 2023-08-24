# Unstandard Library

Our own implementation of C++ std library classes and data structures to investigate impact of different optimizations of performance.

Current Data Structures:
1. Array
2. String
3. Vector
4. Set

Collaborators: Ben, Chris

**Further Notes** ( TO BE REMOVED ): https://docs.google.com/document/d/10WjLhU_cxeN_wvX2Q9tp6nzZyLks1j78UNoN0ND10WI/edit


## Dependencies

(WIP)


## Google Tests Guide

- https://google.github.io/googletest/primer.html


## How to Run In Windows

### With Visual Studio
This project is fully supported in Visual Studio and it should detect the build configurations from the `CMakePresets.json` file.
This allows you to run the different configurations directly from the Visual Studio GUI.

### From Terminal
1. Navigate to the output directory
2. Run cmake to generate the Makefile:
```
cmake {source folder dir} -G {build tool}
```
Example if your output directory is in the source directory and you want to use NMAKE as the build tool:
```
cmake .. -G "Nmake Makefiles"
```
3. Run the build tool to build the executables from the Makefile (In this example, using NMAKE):
```
nmake
```
4. Run the executable. Ex:
```
UTD
```

## How to Run In MacOS | Ubuntu

### From Terminal
1. Navigate to the project directory
```
cd UTD/UTD
```

2. Run cmake to generate make configurations with ./build/ as output dir
```
cmake -B ./build
```

3. Build the project with ./build/ as output dir
```
cmake --build ./build
```

4. Run the program found in build/ dir
```
./build/main
```

5. (Optional) Delete build
```
rm -rf build
```
