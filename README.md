# Easy CMakefile Example

This is an example of an easy-to-understand CMakeLists.txt file for a C++ project using the vcpkg package manager. The CMakeLists.txt file helps you build your C++ project and manage external dependencies effortlessly.

## Prerequisites

Make sure you have the following installed on your system:

- CMake (version 3.20 or higher)
- vcpkg (a package manager for C++ libraries)

## Project Structure

Your project directory should have the following structure:

```
project_root/
  |- CMakeLists.txt
  |- include/
  |    |- ...  # Header files
  |
  |- src/
  |    |- ...  # Source files
  |
  |- lib/
  |    |- ...  # Additional libraries (optional)
  |
  |- bin/
  |    |- ...  # Executables (after building)
  |
  |- build/
  |    |- ...  # Build files (create this directory before running CMake)
  |
  |- ...        # Other project files
```

## CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)
project(test_cmake CXX)

# Specify the path to the vcpkg CMake toolchain file
set(CMAKE_TOOLCHAIN_FILE C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add any additional compiler flags or definitions if needed
# For example, you can define -DCURL_STATICLIB=ON like this:
# add_compile_definitions(-DCURL_STATICLIB=ON)

# Include directories for header files from vcpkg packages
include_directories(
    C:/vcpkg/vcpkg/installed/x64-windows/include
)

# Link directories for library files from vcpkg packages
link_directories(
    C:/vcpkg/vcpkg/installed/x64-windows/lib
)

# Add the path to your own source files (cpp)
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

# Add the path to your own header files (h)
file(GLOB_RECURSE HEADERS
    "include/*.h"
)

# Create the executable (or library)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# If you want to build a static library instead of an executable:
# add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Link the necessary libraries from vcpkg
target_link_libraries(${PROJECT_NAME} PRIVATE
    # List the libraries from vcpkg that you need, if any
    # For example: library1, library2, ...
    libcurl
)

# If you are building a static library, link it like this:
# target_link_libraries(${PROJECT_NAME} PRIVATE
#     library1
#     library2
#     # ...
#     libcurl
# )
```

## Building the Project

1. Create a `build` directory in your project root: `mkdir build`
2. Navigate to the `build` directory: `cd build`
3. Generate the build files using CMake: `cmake ..`
4. Build the project using your preferred build tool (e.g., make, ninja): `cmake --build .`

After building, you'll find the executable (or static library) in the `bin` directory. If you have additional libraries, you can place them in the `lib` directory.

That's it! With this simple CMakeLists.txt, you can manage your C++ project and external dependencies easily, making it easier to share your code with others and collaborate on GitHub. Happy coding!