#include "drawing_funcs.h"
#include "coordinate.h"

const unsigned char p_cosine_msb[8] = {0,0,0,0,0,0,0,1};
const unsigned char p_sine_msb[8] = {1,0,0,0,0,0,0,0};
const unsigned char p_cosine_lsb[8] = {0,56,111,159,200,230,249,0};
const unsigned char p_sine_lsb[8] = {0,249,230,200,159,111,56,0};


coordinate gen_coord(signed char msb, unsigned char lsb){
    coordinate output;
    output.b.msb = msb;
    output.b.lsb = lsb;
    return output;
}

#pragma optimize (push, off)
coordinate gen_x_velocity(const char a_frame, const char a_flip){
    coordinate x_output;
    gen_coord(p_cosine_msb[a_frame], p_cosine_lsb[a_frame]);
    if(a_flip==SPRITE_FLIP_BOTH || a_flip==SPRITE_FLIP_Y){
        x_output.i *= -1;
    }
    x_output.b.lsb = 1;
    x_output.b.lsb = 0;
    return x_output;
}

coordinate gen_y_velocity(const char a_frame, const char a_flip){
    coordinate y_output;
    y_output = gen_coord(p_sine_msb[a_frame], p_sine_lsb[a_frame]);
    if(a_flip==SPRITE_FLIP_NONE || a_flip==SPRITE_FLIP_X){
        y_output.i *= -1;
    }
    return y_output;
}
#pragma optimize (pop)