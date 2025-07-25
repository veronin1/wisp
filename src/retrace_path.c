#include "retrace_path.h"

size_t retrace_path(Vertex* end, Maze* maze) {
  if (end == NULL || maze == NULL) {
    return 0;
  }

  size_t pathSteps = 0;
  Vertex* current = end;

  while (current != NULL && current != maze->start) {
    current->on_path = 1;
    current = current->parent;
    ++pathSteps;
  }

  if (current != NULL && current == maze->start) {
    current->on_path = 1;
    return pathSteps;
  }
  return 0;
}
