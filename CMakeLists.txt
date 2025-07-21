cmake_minimum_required(VERSION 3.10)
project(maze_solver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable clang-tidy if available
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

# Export compile_commands.json (good for clang-tidy and IDEs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add executable from src/main.cpp
add_executable(maze_solver
    src/main.cpp
)

# Include headers from include/
target_include_directories(maze_solver PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Compiler options - warnings, sanitizer, optimizations, hardening
target_compile_options(maze_solver PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wformat=2
    -Wconversion
    -Wnull-dereference
    -Wdouble-promotion
    -Werror
    -fstack-protector-strong
    -D_FORTIFY_SOURCE=2
    -fsanitize=address,undefined
    -O2
)

# Linker flags for sanitizer
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")

# Output the executable to bin/
set_target_properties(maze_solver PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
