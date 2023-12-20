#include "coordinate.h"

coordinate gen_coord(char msb, char lsb){
    coordinate output;
    output.b.msb = msb;
    output.b.lsb = lsb;
    return output;
}