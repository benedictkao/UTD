# Unstandard Library

Our own implementation of C++ std library classes and data structures to investigate impact of different optimizations of performance.

Current Data Structures:
1. Array
2. String
3. Vectors

Collaborators: Ben, Chris

**Further Notes** ( TO BE REMOVED ): https://docs.google.com/document/d/10WjLhU_cxeN_wvX2Q9tp6nzZyLks1j78UNoN0ND10WI/edit


### Dependencies

(WIP)


### Google Tests Guide

- https://google.github.io/googletest/primer.html

### How to Run In Windows
1. Navigate to source directory (UTD folder)
2. If you don't already have a build folder, create one, otherwise skip to step 3
```
mkdir build
```
3. Navigate to the build folder
```
cd build
```
4. Run cmake to generate the Makefile
```
cmake .. -G "Nmake Makefiles"
```
5. Run nmake to build the executables from the Makefile
```
nmake
```
6. Run the executable. Ex:
```
UTD
```