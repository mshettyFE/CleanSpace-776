#ifndef COORDINATE
#define COORDINATE

typedef struct {
    unsigned char lsb;
    signed char msb;
} Fixed;

typedef union coordinate {
    signed int i;
    Fixed b;
} coordinate;

coordinate gen_coord(signed char msb, unsigned char lsb);

coordinate gen_x_accel(const char a_frame, const char a_flip);

coordinate gen_y_accel(const char a_frame, const char a_flip);

#endif