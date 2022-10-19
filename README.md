# nadalib
Simplistic C++ helper library for every day needs like
+ random number generation
+ ini (config) file reading/writing
+ basic logging
+ string manipulation
+ file system

# How to include in your project
1. Git clone or copy folder `libnada` to the same directory your `CMakeLists.txt` is in.
2. Add these lines to your `CMakeLists.txt`
```cmake
    ...
    add_subdirectory(libnada)
    ...
    include_directories(libnada/include)
    ...
    target_link_libraries(PROJECT_NAME PRIVATE nada)
    ...
```
# How to Use
TODO
