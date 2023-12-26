#ifndef DEATH_ANIM
#define DEATH_ANIM

#include "gen/assets/Death.h"
#include "coordinate.h"
#include "List.h"

/*

Death animations.

*/

#define DEATH_FRAME_COUNTER 8 // how long to wait before next frame
#define MAX_DEATH_FRAMES 8 // number of frames in each death animation

// starting location of each death animation in sprite table
#define PLAYER_ONE_DEATH_START 32
#define PLAYER_TWO_DEATH_START 48
#define METOER_RED_DEATH_START 8
#define METOER_DARK_GREEN_DEATH_START 24
#define METEOR_LIGHT_GREEN_DEATH_START 40
#define METOER_PURPLE_DEATH_START 56

struct DeathAnim{
    struct Object* obj;
    char starting_frame;
    char counter; // how long until next frame is played
};

LNode* initDeathAnim(LNode* obj);
LNode* UpdateDeath(struct List* DeathList, LNode* cur);
void freeDeath(LNode* cur);

#endif