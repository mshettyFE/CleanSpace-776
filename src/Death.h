#ifndef DEATH_ANIM
#define DEATH_ANIM

#include "gen/assets/Death.h"
#include "coordinate.h"
#include "List.h"

#define DEATH_FRAME_COUNTER 16
#define MAX_DEATH_FRAMES 8

#define PLAYER_ONE_DEATH_START 32
#define PLAYER_TWO_DEATH_START 48
#define STUPID_DEATH_START 0
#define AGGRO_DEATH_START 16
#define METOER_RED_DEATH_START 8
#define METOER_DARK_GREEN_DEATH_START 24
#define METEOR_LIGHT_GREEN_DEATH_START 40
#define METOER_PURPLE_DEATH_START 56

struct DeathAnim{
    struct Object* obj;
    unsigned char starting_frame;
    unsigned char counter;
};

LNode* initDeathAnim(LNode* obj);
LNode* UpdateDeath(struct List* DeathList, LNode* cur);
void freeDeath(LNode* cur);

#endif