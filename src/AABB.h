#ifndef AXIS_ALIGNED_BOUNDING_BOX
#define AXIS_ALIGNED_BOUNDING_BOX

#include "coordinate.h"

struct AABB{
  char x;
  char y;
  char x_size;
  char y_size;
};


struct AABB* initAABB(const char a_x, const char a_y, const unsigned char size);

void updateAABB(struct AABB* Bound, const char a_x, const char a_y);

void freeAABB(struct AABB* bb);

#endif
