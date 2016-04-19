# bomberman

Here is a simple 2D bomberman.
This project uses:
 - c++ 17
 - CMake as a build system
 - SFML 2 as a 2D librarie


## Build from the source

Your `CMakeCache.txt` must define these variables

  - gtest_include_dir:STRING=/directory/to/gtest/installation/include

  - gtest_lib_dir:STRING=/directory/to/gtest/installation/lib/

  - gtest_libname:STRING=gtest

  - sfml_include_dir:FILEPATH=/directory/to/sfml/installation/include

  - sfml_lib_dir:FILEPATH=/directory/to/sfml/installation/lib

  - sfml_libname_graphics:STRING=libsfml-graphics.so

  - sfml_libname_system:STRING=libsfml-system.so

  - sfml_libname_window:STRING=libsfml-window.so

after that, generate a Makefile with
 ```
 cmake project_directory
 ```

then start compilation with
```
make
```
