#ifndef PLAYER
#define PLAYER

#define PLYR_ONE_ID 0
#define PLYR_TWO_ID 1

#define PLAYER_ONE_STRT_FRAME 0
#define PLAYER_TWO_STRT_FRAME 8

#define BULLET_COOLDOWN 1

#include "input.h"

#include "coordinate.h"
#include "object.h"
#include "List.h"
#include "globals.h"
#include "Bullet.h"

extern coordinate max_speed_squared;

struct Player{
    struct Object* obj;
    unsigned char player_num;
    unsigned char bullet_timer;
};

struct Player* initPlayer(char a_x,  char a_y, char a_bank, unsigned char a_player_num);

void freePlayer(LNode* node);

LNode* UpdatePlayer(struct List* objList, LNode* node);

#endif