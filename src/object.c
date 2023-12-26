#include "object.h"
#include "gametank.h"
#include <stdlib.h>

extern unsigned int XXXXXXXXXXXXXXXXXX;

struct Object* initObject( char a_x,  char a_y,  char a_v_x,  char a_v_y,  char a_size,
  const char **a_sprite_table, char a_sprite_table_bank, char a_bank, char a_cur_frame, char a_cur_flip){
    struct Object *output = malloc(sizeof(struct Object));
    if(!output){return NULL;}
    output->x.b.msb = a_x;
    output->x.b.lsb = 0;
    output->y.b.msb = a_y;
    output->y.b.lsb = 0;
    output->v_x.b.msb = a_v_x;
    output->v_x.b.lsb = 0;
    output->v_y.b.msb = a_v_y;
    output->v_y.b.lsb = 0;
    output->sprite_table = a_sprite_table;
    output->sprite_table_bank = a_sprite_table_bank;
    output->bank = a_bank;
    output->size.b.msb = a_size;
    output->size.b.lsb = 0;
    output->cur_frame = a_cur_frame;
    output->cur_flip = a_cur_flip;
    return output;
}

struct Object* initObjectInt( int  a_x,  int  a_y,  int  a_v_x,  int  a_v_y,  char a_size,
  const char **a_sprite_table, char a_sprite_table_bank, char a_bank, char a_cur_frame, char a_cur_flip){
    struct Object *output = malloc(sizeof(struct Object));
    if(!output){return NULL;}
    output->x.i = a_x;
    output->y.i = a_y;
    output->v_x.i = a_v_x;
    output->v_y.i = a_v_y;
    output->sprite_table = a_sprite_table;
    output->sprite_table_bank = a_sprite_table_bank;
    output->size.b.msb = a_size;
    output->size.b.lsb = 0;
    output->bank = a_bank;
    output->cur_frame = a_cur_frame;
    output->cur_flip = a_cur_flip;
    return output;
}

struct Object* initObjectCoord( coordinate  a_x,  coordinate a_y, coordinate  a_v_x,  coordinate  a_v_y, char a_size,
  const char **a_sprite_table, char a_sprite_table_bank, char a_bank, char a_cur_frame, char a_cur_flip){
    struct Object *output = malloc(sizeof(struct Object));
    if(!output){return NULL;}
    output->x = a_x;
    output->y = a_y;
    output->v_x = a_v_x;
    output->v_y = a_v_y;
    output->sprite_table = a_sprite_table;
    output->sprite_table_bank = a_sprite_table_bank;
    output->bank = a_bank;
    output->size.b.msb = a_size;
    output->size.b.lsb = 0;
    output->cur_frame = a_cur_frame;
    output->cur_flip = a_cur_flip;
    return output;
}

void updateObject(struct Object* obj){
// & with 0x7FFF to prevent overflow. anythinga above 0x7F is 128, which is not a valid index on the screen
  obj->x.i = (obj->x.i+obj->v_x.i) & 0x7FFF;
  obj->y.i = (obj->y.i+obj->v_y.i) & 0x7FFF;
  draw_sprite_frame(obj->sprite_table, obj->sprite_table_bank, obj->x.b.msb, obj->y.b.msb, obj->cur_frame, obj->cur_flip, obj->bank);
}

void freeObj(struct Object* obj){
  free(obj);
}
