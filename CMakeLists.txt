cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0135 NEW)

project(Lab_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIB_NAME Generator_lib)

add_subdirectory(src)
add_subdirectory(app)


