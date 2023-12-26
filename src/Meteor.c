#include "Meteor.h"
#include "gen/assets/Meteor.h"
#include "gen/assets/SmallMeteor.h"

struct Meteor* initMeteor(coordinate a_x, coordinate  a_y, char a_meteor_type){
    struct Meteor* mtr = malloc(sizeof(struct Meteor));
    mtr->meteor_type = a_meteor_type;
    switch (mtr->meteor_type)
    {
    case BIG_METEOR:
        mtr->obj = initObjectInt( a_x.i, a_y.i, gen_rand_x_vel, gen_rand_y_vel ,
             BIG_METEOR_SIZE, &ASSET__Meteor__Meteor_json, METEOR_BANK, gen_big_meteor_frame , SPRITE_FLIP_NONE);
        break;
    case SMALL_METEOR:
        mtr->obj = initObjectInt( a_x.i, a_y.i, gen_rand_x_vel, gen_rand_y_vel ,
             SMALL_METEOR_SIZE, &ASSET__SmallMeteor__SmallMeteor_json, SMALL_METEOR_BANK, gen_small_meteor_frame , SPRITE_FLIP_NONE);
        break;
    }
    return mtr;
}

void freeMeteor(LNode* node){
    struct Meteor* mtr;
    if(node->obj_type != OBJ_METEOR_ID){
        return;
    }
    mtr = (struct Meteor*) node->item;
    freeObj(mtr->obj);
    free(mtr);
}

LNode* UpdateMeteor(struct List* objList, LNode* node){
    struct Meteor* mtr;
    struct LNode* output;
    LNode* nxt;
    if(!node){return NULL;}
    if(node->obj_type != OBJ_METEOR_ID){ return NULL;}
    mtr = (struct Meteor*) node->item;
    if(mtr){
        updateObject(mtr->obj);
        output = node->next;
        return output;
    }
    output = NULL;
    return output;
}