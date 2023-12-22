#ifndef PLAYER
#define PLAYER

#include "coordinate.h"
#include "object.h"
#include "input.h"
#include "Tree.h"

#define PLYR_ONE_ID 0
#define PLYR_TWO_ID 1

#define PLAYER_ONE_STRT_FRAME 0
#define PLAYER_TWO_STRT_FRAME 8

extern coordinate max_speed_squared;

struct Player{
    struct Object* obj;
    char player_num;
};

struct Player* initPlayer(char a_x,  char a_y, char a_bank, char a_player_num);

void freePlayer(struct Player* plyr);

void UpdatePlayer(struct Player* plyr, struct  Head* new_nodes, struct Head* expired_nodes);

#endif