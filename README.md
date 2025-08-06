# wisp

`wisp` is a C program that solves user-selected maze text files using graph traversal algorithms (DFS, BFS, Dijkstra, A*). It also generates mazes using a DFS approach and saves to a file.

## Demo

[![asciicast](https://asciinema.org/a/oAf7IK0auHZlbtkUwObF90hYE.svg)](https://asciinema.org/a/oAf7IK0auHZlbtkUwObF90hYE)

## Usage

```sh
# Solve a maze using Breadth-First Search (BFS)
./wisp -bfs maze.txt

# Solve a maze using Depth-First Search (DFS)
./wisp -dfs maze.txt

# Solve a maze using Dijkstra's algorithm (shortest path with uniform cost)
./wisp -dijkstra maze.txt

# Solve a maze using A* search (heuristic-based shortest path)
./wisp -astar maze.txt

# Generate a random maze of size 25x25 and save it to maze/25.txt
./wisp -gen 25 maze/25.txt
```

## Requirements

-   CMake >= 3.10
-   C compiler (clang/gcc)
-   Unix System (Linux, MacOS, WSL)

## Build Instructions

```sh
mkdir build
cd build
cmake ..
make
```
