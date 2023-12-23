#include "AABB.h"
#include <stdlib.h>

struct AABB* initAABB(const char a_x, const char a_y, const  unsigned char a_size){
  struct AABB* output  = malloc(sizeof(struct AABB));
  output->x = a_x-(a_size)>>1;
  output->y = a_y-(a_size)>>1;
  output->x_size = a_size;
  output->y_size = a_size;
  return output;
}

void updateAABB(struct AABB* Bound, const char a_x, const char a_y){
  Bound->x = a_x-(Bound->x_size)>>1;
  Bound->y = a_y-(Bound->y_size)>>1;
}

void freeAABB(struct AABB* bb){
  free(bb);
}
