#ifndef OBJECT
#define OBJECT

#include "drawing_funcs.h"
#include <stdlib.h>

typedef struct {
    char lsb;
    char msb;
} Fixed;

typedef union {
    int i;
    Fixed b;
} coordinate;

struct Object{
  coordinate x;
  coordinate y;
  coordinate v_x;
  coordinate v_y;
  coordinate size;
  const Frame *sprite_table;
  char sprite_table_bank;
  char bank;
};

struct Object* initObject(  char a_x,  char a_y, char a_v_x, char a_v_y, char a_size,
  const Frame *a_sprite_table, char a_sprite_table_bank,char a_bank);

void ObjectDraw(struct Object* obj, char a_frame, char a_flip);

void MoveObject(struct Object* obj);

#endif
