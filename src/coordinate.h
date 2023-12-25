#ifndef COORDINATE
#define COORDINATE

#include "random.h"

#define gen_rand_x_vel gen_x_accel(rnd_range(0,7), rnd_range(0,4)).i>>2
#define gen_rand_y_vel gen_y_accel(rnd_range(0,7), rnd_range(0,4)).i>>2
#define gen_rand_x gen_coord(rnd_range(0,127),0)
#define gen_rand_y gen_coord(rnd_range(0,127),0)


typedef struct {
    unsigned char lsb;
    signed char msb;
} Fixed;

typedef union coordinate {
    signed int i;
    Fixed b;
} coordinate;

coordinate gen_coord(signed char msb, unsigned char lsb);

coordinate gen_coord_int(signed int i);

coordinate gen_x_accel(const char a_frame, const char a_flip);

coordinate gen_y_accel(const char a_frame, const char a_flip);

#endif