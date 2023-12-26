#include "gen/assets/Bullets.h"

#include "Bullet.h"
#include "player.h"

void ZZZZZZZZZZZZZZZZZZZZZZZZZ(){}

struct Bullet* initBullet(const coordinate* a_x,const  coordinate* a_y, const coordinate*  a_v_x, const coordinate* a_v_y, char a_bank, char origin){
    struct Bullet* blt = malloc(sizeof(struct Bullet));
    if(!blt){return NULL;}
    blt->frame_toggle = 0;
    blt->display_counter = BULLET_FRAME_COUNTER;
    blt->lifetime = BULLET_LIFETIME;

    switch (origin)
    {
        case PLYR_ONE_ID:
            blt->origin = PLYR_ONE_ID;
            blt->obj = initObjectCoord( a_x, a_y, a_v_x, a_v_y, BULLET_SIZE, &ASSET__Bullets__Bullets_json, a_bank, 0, SPRITE_FLIP_NONE);
            break;
        case PLYR_TWO_ID:
            blt->origin = PLYR_TWO_ID;
            blt->obj = initObjectCoord( a_x, a_y, a_v_x, a_v_y, BULLET_SIZE, &ASSET__Bullets__Bullets_json, a_bank, 1, SPRITE_FLIP_NONE);
            break;
    }
    if(blt->obj == NULL){
        free(blt);
        return NULL;
    }
    return blt;
}

void freeBullet(LNode* node){
    struct Bullet* blt;
    if(node->obj_type != OBJ_BULLET_ID){
        ZZZZZZZZZZZZZZZZZZZZZZZZZ();
        return;
    }
    blt = (struct Bullet*) node->item;
    if(blt == NULL){
        return;
    }
    freeObj(blt->obj);
    free(blt);
    free(node);
}

LNode* UpdateBullet(struct List* objList, LNode* node){
    struct Bullet* blt;
    struct LNode* output;
    LNode* nxt;
    if(node == NULL){
        return NULL;
    }
    if(node->obj_type != OBJ_BULLET_ID){
        return NULL;
    }
    blt = (struct Bullet*) node->item;
    if(blt){
        blt->display_counter -= 1;
        blt->lifetime -= 1;
        if(blt->lifetime == 0){
            output =  Remove(objList,node);
            return output;
        }
        if(blt->display_counter == 0){
            blt->display_counter = BULLET_FRAME_COUNTER;
            if(blt->frame_toggle){
                blt->frame_toggle = 0;
                blt->obj->cur_frame = blt->obj->cur_frame-BULLET_FRAME_DELTA;
            }
            else{
                blt->frame_toggle = 1;
                blt->obj->cur_frame = blt->obj->cur_frame+BULLET_FRAME_DELTA;
            }
        }
        updateObject(blt->obj);
        output = node->next;
        return output;
    }
    output = NULL;
    return output;

}