#include "AABB.h"
#include <stdlib.h>

struct AABB* initAABB(coordinate a_x, coordinate a_y, char a_size){
  struct AABB* output  = malloc(sizeof(struct AABB));
  output->x = a_x;
  output->y = a_y;
  output->x_size.b.msb = a_size;
  output->x_size.b.lsb = 0;
  output->y_size.b.msb = a_size;
  output->y_size.b.lsb = 0;
  return output;
}

void freeAABB(struct AABB* bb){
  free(bb);
}
