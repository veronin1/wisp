#include "retrace_path.h"

void retrace_path(Vertex* end, Maze* maze) {
  Vertex* current = end;
  while (current != NULL && current != maze->start) {
    current->parent->on_path = 1;
    current = current->parent;
  }

  if (current == maze->start) {
    current->on_path = 1;
  }
}
