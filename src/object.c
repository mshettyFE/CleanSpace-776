#include "object.h"
#include "AABB.h"
#include <stdlib.h>

struct Object* initObject( const char a_x, const  char a_y, const  char a_v_x,  const char a_v_y, const  unsigned char a_size,
  const char **a_sprite_table, const char a_sprite_table_bank, const char a_bank, const char a_cur_frame, const char a_cur_flip){
    struct Object *output = malloc(sizeof(struct Object));
    output->x.b.msb = a_x;
    output->x.b.lsb = 0;
    output->y.b.msb = a_y;
    output->y.b.lsb = 0;
    output->v_x.b.msb = a_v_x;
    output->v_x.b.lsb = 0;
    output->v_y.b.msb = a_v_y;
    output->v_y.b.lsb = 0;
    output->bounding_box = initAABB(output->x.b.msb,output->y.b.msb, a_size);
    output->sprite_table = a_sprite_table;
    output->sprite_table_bank = a_sprite_table_bank;
    output->bank = a_bank;
    output->cur_frame = a_cur_frame;
    output->cur_flip = a_cur_flip;
    return output;
}

struct Object* initObjectInt( const signed int  a_x, const  signed int  a_y, const  signed int  a_v_x,  const signed int  a_v_y, const unsigned  char a_size,
  const char **a_sprite_table, const char a_sprite_table_bank, const char a_bank, const char a_cur_frame, const char a_cur_flip){
    struct Object *output = malloc(sizeof(struct Object));
    output->x.i = a_x;
    output->y.i = a_y;
    output->v_x.i = a_v_x;
    output->v_y.i = a_v_y;
    output->bounding_box = initAABB(output->x.b.msb,output->y.b.msb, a_size);
    output->sprite_table = a_sprite_table;
    output->sprite_table_bank = a_sprite_table_bank;
    output->bank = a_bank;
    output->cur_frame = a_cur_frame;
    output->cur_flip = a_cur_flip;
    return output;
}

struct Object* initObjectCoord( const coordinate*  a_x, const  coordinate* a_y, const  coordinate*  a_v_x,  const coordinate*  a_v_y, const unsigned  char a_size,
  const char **a_sprite_table, const char a_sprite_table_bank, const char a_bank, const char a_cur_frame, const char a_cur_flip){
    struct Object *output = malloc(sizeof(struct Object));
    output->x = *a_x;
    output->y = *a_y;
    output->v_x = *a_v_x;
    output->v_y = *a_v_y;
    output->bounding_box = initAABB(output->x.b.msb,output->y.b.msb, a_size);
    output->sprite_table = a_sprite_table;
    output->sprite_table_bank = a_sprite_table_bank;
    output->bank = a_bank;
    output->cur_frame = a_cur_frame;
    output->cur_flip = a_cur_flip;
    return output;
}

void updateObject(struct Object* obj){
  obj->x.i += obj->v_x.i;
  obj->y.i += obj->v_y.i;
  updateAABB(obj->bounding_box, obj->x.b.msb, obj->x.b.msb);
  draw_sprite_frame(obj->sprite_table, obj->sprite_table_bank, obj->x.b.msb, obj->y.b.msb, obj->cur_frame, obj->cur_flip, obj->bank);
}

coordinate getSpeedSquared(struct Object* obj){
  coordinate output;
  output.i = obj->v_x.i*obj->v_x.i+obj->v_y.i*obj->v_y.i;
  return output;
}

void freeObj(struct Object* obj){
  freeAABB(obj->bounding_box);
  free(obj);
}
