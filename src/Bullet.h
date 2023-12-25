#ifndef BULLET
#define BULLET

#include "coordinate.h"
#include "object.h"
#include "List.h"

#define ORIGIN_P1 0
#define ORIGIN_P2 1
#define ORIGIN_STUPID 2
#define ORIGIN_AGGRO 3

#define BULLET_FRAME_COUNTER 30
#define BULLET_FRAME_DELTA 4
#define BULLET_LIFETIME 100

struct Bullet{
    struct Object* obj;
    unsigned char frame_toggle;
    unsigned char display_counter;
    unsigned char lifetime;
    unsigned char origin;
};

struct Bullet* initBullet(const coordinate* a_x,  const coordinate* a_y, const coordinate*  a_v_x, const  coordinate* a_v_y, char a_bank, char origin);
//struct Bullet* initBullet(const signed int a_x,  const signed int a_y, const signed int  a_v_x, const signed int a_v_y, char a_bank, char origin);

void freeBullet(LNode* node);
LNode* UpdateBullet(struct List* objList, LNode* node);


#endif