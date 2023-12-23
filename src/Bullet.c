#include "gen/assets/Bullets.h"

#include "Bullet.h"

struct Bullet* initBullet(const signed int a_x,  const signed int  a_y, const signed int  a_v_x, const signed int  a_v_y, char a_bank, char origin){
    struct Bullet* blt = malloc(sizeof(struct Bullet));
    blt->frame_toggle = 0;
    blt->display_counter = BULLET_FRAME_COUNTER;

    blt->obj = initObject( a_x, a_y, a_v_x, a_v_y, 4, &ASSET__Bullets__Bullets_json, a_bank, origin, SPRITE_FLIP_NONE);
    return blt;
}

void freeBullet(struct Bullet* blt){
    freeObj(blt->obj);
    free(blt);
}

void UpdateBullet(struct Bullet* blt, struct  Head* new_nodes, struct Head* expired_nodes){
    blt->display_counter -= 1;
    if(blt->display_counter == 0){
        blt->display_counter = BULLET_FRAME_COUNTER;
        blt->frame_toggle = !blt->frame_toggle;
        if(blt->frame_toggle){
            blt->obj->cur_frame = blt->obj->cur_frame+BULLET_FRAME_DELTA;
        }
        else{
            blt->obj->cur_frame = blt->obj->cur_frame-BULLET_FRAME_DELTA;
        }
    }

    updateObject(blt->obj);
}