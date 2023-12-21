#ifndef OBJECT
#define OBJECT

#include "drawing_funcs.h"
#include "coordinate.h"
#include "AABB.h"
#include <stdlib.h>

struct Object{
  coordinate x;
  coordinate y;
  coordinate v_x;
  coordinate v_y;
  struct AABB* bounding_box;
  coordinate size;
  const char **sprite_table;
  char sprite_table_bank;
  char bank;
};

struct Object* initObject( const char a_x, const  char a_y, const  char a_v_x,  const char a_v_y, const  char a_size,
  const char **a_sprite_table, const char a_sprite_table_bank, const char a_bank);

struct Object* initObjectCoord( const coordinate a_x, const  coordinate a_y, const  coordinate a_v_x,  const coordinate a_v_y, const  char a_size,
  const char **a_sprite_table, const char a_sprite_table_bank, const char a_bank);

void ObjectDraw(struct Object* obj, char a_frame, char a_flip);

void MoveObject(struct Object* obj);

#endif
