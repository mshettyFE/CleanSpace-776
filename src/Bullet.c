#include "gen/assets/Bullets.h"

#include "Bullet.h"
#include "player.h"

struct Bullet* initBullet(const coordinate* a_x,const  coordinate* a_y, const coordinate*  a_v_x, const coordinate* a_v_y, char a_bank, char origin){
    struct Bullet* blt = malloc(sizeof(struct Bullet));
    blt->frame_toggle = 0;
    blt->display_counter = BULLET_FRAME_COUNTER;
    blt->lifetime = BULLET_LIFETIME;

    switch (origin)
    {
        case 0:
            blt->obj = initObjectCoord( a_x, a_y, a_v_x, a_v_y, 5, &ASSET__Bullets__Bullets_json, a_bank, 0, SPRITE_FLIP_NONE);
            break;
        case 1:
            blt->obj = initObjectCoord( a_x, a_y, a_v_x, a_v_y, 5, &ASSET__Bullets__Bullets_json, a_bank, 1, SPRITE_FLIP_NONE);
            break;
    }
    return blt;
}

void freeBullet(struct Bullet* blt){
    freeObj(blt->obj);
    free(blt);
}

void UpdateBullet(struct Bullet* blt, struct Head* cur_nodes, struct  Head* new_nodes, struct Head* expired_nodes){
    blt->display_counter -= 1;
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
}