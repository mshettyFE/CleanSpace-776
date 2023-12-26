#ifndef PLAYER
#define PLAYER

#define PLYR_ONE_ID 0
#define PLYR_TWO_ID 1

#define PLAYER_ONE_STRT_FRAME 0
#define PLAYER_TWO_STRT_FRAME 8

#define BULLET_COOLDOWN 50 // Number of frames before a bullet can be shoot again

#include "input.h"

#include "coordinate.h"
#include "object.h"
#include "List.h"
#include "globals.h"
#include "Bullet.h"

struct Player{
    struct Object* obj;
    char player_num;
    char bullet_timer; // how long until you can shoot again
};

struct Player* initPlayer(char a_x,  char a_y, char a_bank, char a_player_num);

void freePlayer(LNode* node);

LNode* UpdatePlayer(struct List* objList, LNode* node);

#endif