cmake_minimum_required(VERSION 3.0)
project(YourProjectName)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add your source files
set(SOURCES
    src/main.cpp
    src/foo.cpp
    src/bar.cpp
)

# Add your header files
set(HEADERS
    include/foo.h
    include/bar.h
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set additional compiler flags (optional)
# For example, to enable warnings:
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
target_compile_options(${PROJECT_NAME} PRIVATE -std=c++17 -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system)

# Specify include directories (optional)
# For example, if your headers are in the "include" directory:
# target_include_directories(${PROJECT_NAME} PRIVATE include)
