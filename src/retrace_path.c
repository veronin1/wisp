#include "retrace_path.h"

size_t retrace_path(Vertex* end, Maze* maze) {
  Vertex* current = end;
  size_t pathSteps = 0;
  while (current != NULL && current != maze->start) {
    current->on_path = 1;
    current = current->parent;
    ++pathSteps;
  }

  if (current == maze->start) {
    current->on_path = 1;
    return pathSteps;
  }
  return 0;
}
