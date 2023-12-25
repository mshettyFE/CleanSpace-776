#include "Death.h"
#include "player.h"
#include "Bullet.h"
#include "object.h"
#include "globals.h"
#include <stdlib.h>

extern unsigned int AAAAAAAAAAAAAAAAAA ;
extern unsigned int OOOOOOOOOOOOOOOOOO ;
extern unsigned int XXXXXXXXXXXXXXXXXX ;
extern unsigned int YYYYYYYYYYYYYYYYYY ;
extern void ZZZZZZZZZZZZZZZZZZZZZZZ();


LNode* initDeathAnim(LNode* node){
    struct Player* pid;
    struct Bullet* bid;
    struct DeathAnim* anim;
    LNode* out;
    if(node){
      anim = malloc(sizeof(struct DeathAnim));
        switch (node->obj_type)
        {
        case OBJ_PLAYER_ID:
            pid = (struct Player*) node->item;
            if(pid == NULL){
                free(anim);
                return NULL;
            }
            switch (pid->player_num)
            {
            case PLYR_ONE_ID:
                anim->starting_frame = PLAYER_ONE_DEATH_START;
                break;
            case PLYR_TWO_ID:
                anim->starting_frame = PLAYER_TWO_DEATH_START;
                break;
            }
                anim->obj = initObject(pid->obj->x.b.msb, pid->obj->y.b.msb, 0, 0, DEATH_ANIM_SIZE,&ASSET__Death__Death_json, DEATH_BANK, anim->starting_frame, SPRITE_FLIP_NONE);
            break;
        case OBJ_BULLET_ID:
            free(anim);
            return NULL;
            break;
        case OBJ_METEOR_ID:
            free(anim);
            return NULL;
            break;        
        }
    anim->counter = 0;
    out  = malloc(sizeof(LNode));
    out->item = anim;
    out->obj_type = OBJ_DEATH_ID;
    return out;
    }
    return NULL;
}

LNode* UpdateDeath(struct List* DeathList, LNode* cur){
    struct DeathAnim* anim;
    struct Object* obj;
    if(!cur){return NULL;}
    anim = (struct DeathAnim*) cur->item;
    if(!anim){return NULL;}
    updateObject(anim->obj);
    anim->counter += 1;
    if(anim->counter >= DEATH_FRAME_COUNTER){
        anim->counter = 0;
        anim->obj->cur_frame += 1;
    }
    if(anim->obj->cur_frame >= (anim->starting_frame+MAX_DEATH_FRAMES) ){
        return RemoveDeath(DeathList, cur, freeDeath);
    }
    return cur->next;
}

void freeDeath(LNode* cur){
    struct DeathAnim* d;
    if(!cur){return;}
    d = (struct DeathAnim*) cur->item;
    if(d == NULL){
        return;
    }
    freeObj(d->obj);
    free(d);
    free(cur);
}

