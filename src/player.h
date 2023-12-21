#ifndef PLAYER
#define PLAYER

#include "coordinate.h"
#include "object.h"
#include "input.h"

#define PLYR_ONE_ID 0
#define PLYR_TWO_ID 1

#define PLAYER_ONE_STRT_FRAME 0
#define PLAYER_TWO_STRT_FRAME 8

struct Player{
    struct Object* obj;
    char player_num;
    char cur_frame;
    char cur_flip;
    char plyr_index;
};

struct Player* initPlayer(char a_x,  char a_y, char a_bank, char a_player_num);

void DrawPlayer(struct Player* plyr);

void PlayerUpdate(struct Player* plyr, const coordinate max_speed_squared);

#endif