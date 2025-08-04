#include "a_star.h"
#include "globals.h"
#include "maze.h"
#include "min_heap.h"

#include <limits.h>
#include <stdlib.h>

static int directionX[4] = {0, 0, -1, 1};
static int directionY[4] = {-1, 1, 0, 0};

typedef struct AStar {
  int g_score;
  int h_score;
  int f_score;
  struct AStar* parent;
  Vertex* vertex;
} AStar;

AStar a_star_node[MAX_HEIGHT][MAX_WIDTH];

int calculate_heuristic(Vertex* start, Vertex* end) {
  return abs((int)start->x - (int)end->x) + abs((int)start->y - (int)end->y);
}

int a_star(Maze* maze) {
  MinHeap open_set;
  open_set.size = 0;

  for (size_t i = 0; i < maze->height; ++i) {
    for (size_t j = 0; j < maze->width; ++j) {
      AStar* current = &a_star_node[i][j];
      current->g_score = INT_MAX;
      current->h_score = calculate_heuristic(&maze->grid[i][j], maze->end);
      current->f_score = INT_MAX;
      current->parent = NULL;
      maze->grid[i][j].visited = 0;
    }
  }

  size_t startY = maze->start->y;
  size_t startX = maze->start->x;

  a_star_node[startY][startX].g_score = 0;
  a_star_node[startY][startX].f_score = a_star_node[startY][startX].h_score;
  heapPush(&open_set, maze->start, a_star_node[startY][startX].f_score);

  while (open_set.size != 0) {
    HeapNode current_node = extract_min(&open_set);
    Vertex* current = current_node.vertex;

    if (current == maze->end) {
      return A_STAR_SUCCESS;
    }

    if (current->visited) {
      continue;
    }
    current->visited = 1;
    ++totalSteps;

    for (size_t i = 0; i < 4; ++i) {
      int neighbourX = (int)current->x + directionX[i];
      int neighbourY = (int)current->y + directionY[i];

      if (neighbourX >= 0 && neighbourX < (int)maze->width && neighbourY >= 0 &&
          neighbourY < (int)maze->height) {
        Vertex* neighbour_vertex = &maze->grid[neighbourY][neighbourX];
        if (neighbour_vertex->is_wall || neighbour_vertex->visited) {
          continue;
        }

        AStar* currentStarNode = &a_star_node[current->y][current->x];
        AStar* neighbour = &a_star_node[neighbourY][neighbourX];

        int tentative_gScore = currentStarNode->g_score + 1;
        if (tentative_gScore < neighbour->g_score) {
          neighbour->g_score = tentative_gScore;
          neighbour->f_score = tentative_gScore + neighbour->h_score;
          neighbour->parent = currentStarNode;
          heapPush(&open_set, neighbour_vertex, neighbour->f_score);
        }
      }
    }
  }

  return A_STAR_FAILURE;
}
