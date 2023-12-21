#ifndef AXIS_ALIGNED_BOUNDING_BOX
#define AXIS_ALIGNED_BOUNDING_BOX

#include "coordinate.h"

struct AABB{
  coordinate x;
  coordinate y;
  coordinate x_size;
  coordinate y_size;
};


struct AABB* initAABB(coordinate a_x, coordinate a_y, char size);

void freeAABB(struct AABB* bb);

#endif
