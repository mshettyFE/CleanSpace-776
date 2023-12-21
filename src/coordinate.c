#include "drawing_funcs.h"
#include "coordinate.h"

const signed char p_cosine_msb[8] = {0,0,0,0,0,0,0,1};
const signed char p_sine_msb[8] = {1,0,0,0,0,0,0,0};
const unsigned char p_cosine_lsb[8] = {0,56,111,159,200,230,249,0};
const unsigned char p_sine_lsb[8] = {0,249,230,200,159,111,56,0};


coordinate gen_coord(const signed char msb, const  unsigned char lsb){
    coordinate output;
    output.b.msb = msb;
    output.b.lsb = lsb;
    return output;
}
coordinate gen_x_accel(const char a_frame, const char a_flip){
/*
  NONE: <1,1> => <1,-1>
  X: <1,-1> => <1,1>
  BOTH: <-1,-1> => <-1,1>
  Y: <-1,1> => <-1,-1>
*/
    coordinate x_output;
    x_output = gen_coord(p_cosine_msb[a_frame], p_cosine_lsb[a_frame]);
    if(a_flip==SPRITE_FLIP_BOTH  || a_flip==SPRITE_FLIP_X){
        x_output.i *= -1;
    }
    return x_output;
}

coordinate gen_y_accel(const char a_frame, const char a_flip){
    coordinate y_output;
    y_output = gen_coord(p_sine_msb[a_frame], p_sine_lsb[a_frame]);
    if(a_flip==SPRITE_FLIP_NONE || a_flip==SPRITE_FLIP_X){
        y_output.i *= -1;
    }
    return y_output;
}