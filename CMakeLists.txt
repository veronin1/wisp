cmake_minimum_required(VERSION 3.10)
project(maze_solver C)

# Use Clang explicitly
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_CLANG_TIDY "clang-tidy")

# Export compile commands for clang-tidy + LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output to ./bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Source files
add_executable(soniq
    src/main.c
    src/maze_parser.c
)

# Include directory
target_include_directories(maze_solver PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Compiler flags for max safety & speed
target_compile_options(maze_solver PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wformat=2
    -Wcast-align
    -Wconversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
    -Wmissing-prototypes
    -Wstrict-prototypes
    -Wold-style-definition
    -Werror
    -fstack-protector-strong
    -D_FORTIFY_SOURCE=2
    -fsanitize=address
    -O3
    -g
)

# Linker flags (AddressSanitizer)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
