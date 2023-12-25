#ifndef METEOR
#define METEOR

#include "coordinate.h"
#include "object.h"
#include "List.h"
#include "globals.h"
#include "random.h"


#define BIG_METEOR 0
#define SMALL_METEOR 1

#define MAX_BIG_METEOR_FRAMES 8
#define MAX_SMALL_METEOR_FRAMES 16

#define gen_big_meteor_frame rnd_range(1,MAX_BIG_METEOR_FRAMES)
#define gen_small_meteor_frame rnd_range(1,MAX_SMALL_METEOR_FRAMES)


struct Meteor{
    struct Object* obj;
    unsigned char meteor_type;
};

struct Meteor* initMeteor(const coordinate a_x,const  coordinate  a_y, char a_meteor_type);
void freeMeteor(LNode* node);
LNode* UpdateMeteor(struct List* objList, LNode* node, struct List* Death);

#endif