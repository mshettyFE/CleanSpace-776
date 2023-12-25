#include <stdlib.h>
#include "object.h"
#include "player.h"
#include "input.h"
#include "drawing_funcs.h"
#include "coordinate.h"
#include "globals.h"

#include <stdlib.h>

#include "gen/assets/Small.h"
#include "Bullet.h"

extern unsigned char player_1_present;
extern unsigned char player_2_present;
//#define MONITOR_P1

struct Player* initPlayer(  char a_x,  char a_y, char a_bank, unsigned char a_player_num){
    struct Player* plyr = malloc(sizeof(struct Player));
    plyr->player_num = a_player_num;
    plyr->bullet_timer = BULLET_COOLDOWN;
    switch (plyr->player_num)
    {
    case PLYR_ONE_ID:
        plyr->obj = initObject( a_x, a_y, 0, 0, PLAYER_SIZE, &ASSET__Small__Small_json, a_bank, PLAYER_ONE_STRT_FRAME, SPRITE_FLIP_NONE);
        break;
    case PLYR_TWO_ID:
        plyr->obj = initObject( a_x, a_y, 0, 0, PLAYER_SIZE, &ASSET__Small__Small_json, a_bank, PLAYER_TWO_STRT_FRAME, SPRITE_FLIP_NONE);
        break;    
    default:
        break;
    }
    return plyr;
}

void freePlayer(LNode* node){
    struct Player* plyr;
    if(node->obj_type != OBJ_PLAYER_ID){
        return;
    }
    plyr = (struct Player*) node->item;
    if(plyr == NULL){
        return;
    }
    freeObj(plyr->obj);
    free(plyr);
    free(node);
}

LNode* UpdatePlayer(struct List* objList, LNode* node){
    int player_inpts;
    int old_player_inpts;
    char switch_flip=0;
    unsigned char index;
    struct Bullet* blt;
    struct Player* plyr;
    coordinate acceleration_x;
    coordinate acceleration_y;
    coordinate bullet_vel_x;
    coordinate bullet_vel_y;
    coordinate bullet_pos_x;
    coordinate bullet_pos_y;

    if(node){
        if(node->obj_type != OBJ_PLAYER_ID ){
            return NULL;
        }
        plyr = (struct Player*) node->item;

#ifdef MONITOR_P1
        XXXXXXXXXXXXXXXXXX = plyr->obj->x.i;
        YYYYYYYYYYYYYYYYYY = plyr->obj->y.i;
        ZZZZZZZZZZZZZZZZZZZZZZZ();

#endif

        if(plyr->bullet_timer >0){
            plyr->bullet_timer -= 1;
        }

        switch (plyr->player_num){
        case PLYR_ONE_ID:
            player_1_present = 1;
            player_inpts = player1_buttons;
            old_player_inpts = player1_old_buttons;
            index = plyr->obj->cur_frame - PLAYER_ONE_STRT_FRAME;
            break;
        case PLYR_TWO_ID:
            player_2_present = 1;
            player_inpts = player2_buttons;
            old_player_inpts = player2_old_buttons;
            index = plyr->obj->cur_frame - PLAYER_TWO_STRT_FRAME;
            break;
        }
        
        if(player_inpts & INPUT_MASK_RIGHT){
            switch (plyr->obj->cur_flip)
            {
                case SPRITE_FLIP_NONE:
                    if(index==7){
                        plyr->obj->cur_flip = SPRITE_FLIP_Y;
                        break;
                    }
                    index += 1;
                    break;

                case SPRITE_FLIP_Y:
                    if(index==0){
                        plyr->obj->cur_flip = SPRITE_FLIP_BOTH;
                        break;
                    }
                    index -= 1;
                    break;
                case SPRITE_FLIP_BOTH:
                    if(index==7){
                        plyr->obj->cur_flip = SPRITE_FLIP_X;
                        break;
                    }
                    index += 1;
                    break;        
                case SPRITE_FLIP_X:
                    if(index==0){
                        plyr->obj->cur_flip = SPRITE_FLIP_NONE;
                        break;
                    }
                    index -= 1;
                    break;
            }
        }
        if(player_inpts & INPUT_MASK_LEFT){
            switch (plyr->obj->cur_flip)
            {
                case SPRITE_FLIP_NONE:
                    if(index==0){
                        plyr->obj->cur_flip = SPRITE_FLIP_X;
                        break;
                    }
                    index -= 1;
                    break;

                case SPRITE_FLIP_Y:
                    if(index==7){
                        plyr->obj->cur_flip = SPRITE_FLIP_NONE;
                        break;
                    }
                    index += 1;
                    break;
                case SPRITE_FLIP_BOTH:
                    if(index==0){
                        plyr->obj->cur_flip = SPRITE_FLIP_Y;
                        break;
                    }
                    index -= 1;
                    break;        
                case SPRITE_FLIP_X:
                    if(index==7){
                        plyr->obj->cur_flip = SPRITE_FLIP_BOTH;
                        break;
                    }
                    index += 1;
                    break;
            }
        }

        switch(plyr->player_num){
            case PLYR_ONE_ID:
                plyr->obj->cur_frame = index + PLAYER_ONE_STRT_FRAME;
                break;
            case PLYR_TWO_ID:
                plyr->obj->cur_frame = index + PLAYER_TWO_STRT_FRAME;
                break;
        }

        acceleration_x = gen_x_accel(index,plyr->obj->cur_flip);
        acceleration_x.i = acceleration_x.i>>1;
        acceleration_y = gen_y_accel(index,plyr->obj->cur_flip);
        acceleration_y.i = acceleration_y.i>>1;
        
        if(player_inpts & INPUT_MASK_UP) {

            plyr->obj->v_x.i = acceleration_x.i;
            plyr->obj->v_y.i = acceleration_y.i;
        }

        if(player_inpts & INPUT_MASK_DOWN) {
            plyr->obj->v_x.i = -1*acceleration_x.i;
            plyr->obj->v_y.i = -1*acceleration_y.i;
        }


        if(player_inpts & INPUT_MASK_A) {
            if(plyr->bullet_timer == 0){
                plyr->bullet_timer = BULLET_COOLDOWN;
                bullet_vel_x.i = acceleration_x.i<<1;
                bullet_vel_y.i = acceleration_y.i<<1;
                bullet_pos_x = plyr->obj->x;
                bullet_pos_y = plyr->obj->y;
                blt = initBullet(&bullet_pos_x, &bullet_pos_y, &bullet_vel_x, &bullet_vel_y, BULLET_BANK,plyr->player_num);
                AddToHead(objList,blt, OBJ_BULLET_ID);
            }
        }

        updateObject(plyr->obj);
        return node->next;
    }
    return NULL;

}
