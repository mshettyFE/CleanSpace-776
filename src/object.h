#ifndef OBJECT
#define OBJECT

/*

Encodes things with the following properties:
  * Has 2D position and velocity
  * Can collide with other things
  * Can be drawn to the screen
*/


#include "drawing_funcs.h"
#include "coordinate.h"
#include <stdlib.h>


struct Object{
  coordinate x;
  coordinate y;
  coordinate v_x;
  coordinate v_y;
  coordinate size; // Uses AABB for collision detection. size represents half width and half height. All sprites are square, so this works out.
  const char **sprite_table;
  char sprite_table_bank;
  char bank;
  char cur_frame;
  char cur_flip;
};

struct Object* initObject( char a_x, char a_y, char a_v_x,  char a_v_y,  char a_size,
  const char **a_sprite_table, char a_sprite_table_bank, char a_bank, char a_cur_frame, char a_cur_flip);

struct Object* initObjectInt( int  a_x,  int  a_y,  int  a_v_x,  int  a_v_y,  char a_size,
  const char **a_sprite_table, char a_sprite_table_bank, char a_bank, char a_cur_frame, char a_cur_flip);

struct Object* initObjectCoord( coordinate  a_x, coordinate a_y, coordinate  a_v_x,  coordinate  a_v_y, char a_size,
  const char **a_sprite_table, char a_sprite_table_bank, char a_bank, char a_cur_frame, char a_cur_flip);

void freeObj(struct Object* obj);

void updateObject(struct Object* obj);

#endif
