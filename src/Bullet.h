#ifndef BULLET
#define BULLET

#include "coordinate.h"
#include "object.h"
#include "List.h"

/*

Bullets generated by the player. Don't interact with yourself.

*/

#define ORIGIN_P1 0
#define ORIGIN_P2 1

#define BULLET_FRAME_COUNTER 10 // how many frames to wait before toggling frames
#define BULLET_FRAME_DELTA 4 // number of frames between successive frames in sprite sheet
#define BULLET_LIFETIME 100 // max lifetime of bullet

struct Bullet{
    struct Object* obj;
    unsigned char frame_toggle; // which frame to display
    unsigned char display_counter; // how long until frame change
    unsigned char lifetime; // how long until removed from screen
    unsigned char origin; // which player the bullet can from (prevents self annihilation)
};

struct Bullet* initBullet(coordinate a_x,  coordinate a_y, coordinate  a_v_x,  coordinate a_v_y, char a_bank, char origin);

void freeBullet(LNode* node);
LNode* UpdateBullet(struct List* objList, LNode* node);


#endif