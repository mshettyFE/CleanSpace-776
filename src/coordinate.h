#ifndef COORDINATE
#define COORDINATE

/*

Q8.8 fixed point representation. Needed to do rotations.

*/

#include "random.h"

/*
There are 8 possible values of sine and cosine defined.
There are 4 possible flips you can make to these values.
We down shift by 2 since otherwise, things to fast. too fast.
*/

#define gen_rand_x_vel gen_x_vel(rnd_range(0,7), rnd_range(0,4)).i>>2
#define gen_rand_y_vel gen_y_vel(rnd_range(0,7), rnd_range(0,4)).i>>2

// GameTank screen dimensions is 128x128

#define gen_rand_x create_coord(rnd_range(0,127),0)
#define gen_rand_y create_coord(rnd_range(0,127),0)

// top 8 bits are pixel position. bottom 8 bits are sub pixel position

typedef struct {
    char lsb;
    char msb;
} Fixed;

// toggle between signed int (to do  multiplication by -1 and easier math) or Fixed (to get pixel positions)

typedef union coordinate {
    signed int i;
    Fixed b;
} coordinate;

coordinate create_coord(char msb, char lsb);

coordinate gen_x_vel(char a_frame, char a_flip);

coordinate gen_y_vel(char a_frame, char a_flip);

#endif