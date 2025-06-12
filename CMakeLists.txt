cmake_minimum_required(VERSION 3.24)
project(MyHttpServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable warnings
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Add executables
add_executable(my_http_server
    src/Main.cpp
    src/Server.cpp
    src/Server.hpp
)

# Include directory
target_include_directories(my_http_server PRIVATE src)