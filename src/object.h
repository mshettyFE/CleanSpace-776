#ifndef OBJECT
#define OBJECT

#include "drawing_funcs.h"
#include "coordinate.h"
#include <stdlib.h>

struct Object{
  coordinate x;
  coordinate y;
  coordinate v_x;
  coordinate v_y;
  coordinate size;
  const char **sprite_table;
  char sprite_table_bank;
  char bank;
  char cur_frame;
  char cur_flip;
};

struct Object* initObject( const char a_x, const  char a_y, const  char a_v_x,  const char a_v_y, const  unsigned char a_size,
  const char **a_sprite_table, const char a_sprite_table_bank, const char a_bank, const char a_cur_frame, const char a_cur_flip);

struct Object* initObjectInt( const signed int a_x, const  signed int  a_y, const  signed int  a_v_x,  const signed int  a_v_y, const unsigned char a_size,
  const char **a_sprite_table, const char a_sprite_table_bank, const char a_bank , const char a_cur_frame, const char a_cur_flip);

struct Object* initObjectCoord( const coordinate*  a_x, const  coordinate* a_y, const  coordinate*  a_v_x,  const coordinate*  a_v_y, const unsigned char a_size,
  const char **a_sprite_table, const char a_sprite_table_bank, const char a_bank, const char a_cur_frame, const char a_cur_flip);

void freeObj(struct Object* obj);

void updateObject(struct Object* obj);

coordinate getSpeedSquared(struct Object* obj);

#endif
