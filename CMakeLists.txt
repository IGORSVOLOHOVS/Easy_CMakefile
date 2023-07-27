cmake_minimum_required(VERSION 3.20)
project(test_cmake CXX)

# Указываем путь к файлу CMakeLists.txt для vcpkg
set(CMAKE_TOOLCHAIN_FILE C:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Устанавливаем стандарт C++ на C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(-DCURL_STATICLIB=ON)

# Указываем директории с заголовочными файлами и библиотеками из vcpkg
include_directories(
    C:/vcpkg/vcpkg/installed/x64-windows/include
)

link_directories(
    C:/vcpkg/vcpkg/installed/x64-windows/lib
)

# Добавляем путь к собственным исходным файлам (cpp)
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

# Добавляем путь к заголовочным файлам (h)
file(GLOB_RECURSE HEADERS
    "include/*.h"
)

# Создаем исполняемый файл (или библиотеку)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Если вам нужно собрать статическую библиотеку вместо исполняемого файла:
# add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Линковка с библиотеками из vcpkg
target_link_libraries(${PROJECT_NAME} PRIVATE
    # Укажите библиотеки из vcpkg, которые вам нужны
#    library1
#    library2
    # ...
    libcurl
)

# Если вы собираете статическую библиотеку, линкуйте ее так:
 target_link_libraries(${PROJECT_NAME} PRIVATE
#     library1
#     library2
#     # ...
libcurl
 )

