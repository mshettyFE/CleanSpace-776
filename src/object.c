#include "object.h"

struct Object* initObject( const char a_x, const  char a_y, const  char a_v_x,  const char a_v_y, const  char a_size,
  const char **a_sprite_table, const char a_sprite_table_bank, const char a_bank){
    struct Object *output = malloc(sizeof(struct Object));
    output->x.b.msb = a_x;
    output->x.b.lsb = 0;
    output->y.b.msb = a_y;
    output->y.b.lsb = 0;
    output->v_x.b.msb = a_v_x;
    output->v_x.b.lsb = 0;
    output->v_y.b.msb = a_v_y;
    output->v_y.b.lsb = 0;
    output->size = a_size;
    output->sprite_table = a_sprite_table;
    output->sprite_table_bank = a_sprite_table_bank;
    output->bank = a_bank;
    return output;
}

struct Object* initObjectCoord( const coordinate a_x, const  coordinate a_y, const  coordinate a_v_x,  const coordinate a_v_y, const  char a_size,
  const char **a_sprite_table, const char a_sprite_table_bank, const char a_bank){
    struct Object *output = malloc(sizeof(struct Object));
    output->x = a_x;
    output->y = a_y;
    output->v_x = a_v_x;
    output->v_y = a_v_y;
    output->size = a_size;
    output->sprite_table = a_sprite_table;
    output->sprite_table_bank = a_sprite_table_bank;
    output->bank = a_bank;
    return output;  
}


void ObjectDraw(struct Object* obj, char a_frame, char a_flip){
  draw_sprite_frame(obj->sprite_table, obj->sprite_table_bank, obj->x.b.msb, obj->y.b.msb, a_frame, a_flip, obj->bank);
}

void MoveObject(struct Object* obj){
  obj->x.i += obj->v_x.i;
  obj->y.i += obj->v_y.i;
/*
  if(obj->x.b.msb == 1) {
      obj->v_x.b.msb = 1;
  } else if(obj->x.b.msb == 119) {
      obj->v_x.b.msb = -1;
  }
  if(obj->y.b.msb == 8) {
      obj->v_y.b.msb = 1;
  } else if(obj->y.b.msb ==  112) {
      obj->v_y.b.msb = -1;
  }
*/
}