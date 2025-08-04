#include "a_star.h"
#include "maze.h"
#include "min_heap.h"

#include <limits.h>
#include <stdlib.h>

static int directionX[4] = {0, 0, -1, 1};
static int directionY[4] = {-1, 1, 0, 0};

typedef struct {
  int g_score;
  int h_score;
  int f_score;
  Vertex* parent;
} AStar;

int heuristic[MAX_HEIGHT][MAX_WIDTH];
AStar a_star_node[MAX_HEIGHT][MAX_WIDTH];

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
    }
  }

  a_star_node[maze->start->y][maze->start->x].g_score = 0;
  int f_score_start = a_star_node[maze->start->y][maze->start->x].g_score +
                      a_star_node[maze->start->y][maze->start->x].h_score;
  heapPush(&open_set, maze->start, f_score_start);

  while (open_set.size != 0) {
    HeapNode current_node = extract_min(&open_set);
    Vertex* current = current_node.vertex;

    if (current == maze->end) {
      return A_STAR_SUCCESS;
    }

    for (size_t i = 0; i < 4; ++i) {
      int neighbourX = (int)current_node.vertex->x + directionX[i];
      int neighbourY = (int)current_node.vertex->y + directionY[i];

      if (neighbourX >= 0 && neighbourX < (int)maze->width && neighbourY >= 0 &&
          neighbourY < (int)maze->height) {
        AStar* neighbour = &a_star_node[neighbourY][neighbourX];

        int tentative_gScore = a_star_node[current->y][current->x].g_score + 1;
        if (tentative_gScore < neighbour->g_score) {
          neighbour->g_score = tentative_gScore;
          neighbour->f_score = tentative_gScore + neighbour->h_score;
          neighbour->parent = current;
          heapPush(&open_set, &maze->grid[neighbourY][neighbourX],
                   neighbour->f_score);
        }
      }
    }
  }

  return A_STAR_FAILURE;
}

// use manhattan distance (taxicab distance)
int calculate_heuristic(Vertex* start, Vertex* end) {
  return abs((int)start->x - (int)end->x) + abs((int)start->y - (int)end->y);
}
