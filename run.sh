#!/bin/sh

cd bin
./wisp -dijkstra ../maze/99x99.txt 
./wisp -bfs ../maze/99x99.txt
./wisp -dfs ../maze/99x99.txt
./wisp -astar ../maze/99x99.txt
