#ifndef COORDINATE
#define COORDINATE

typedef struct {
    char lsb;
    char msb;
} Fixed;

typedef union coordinate {
    unsigned int i;
    Fixed b;
} coordinate;

coordinate gen_coord(char msb, char lsb);

#endif