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
#include "dynawave.h"
#include "music.h"

// flags to see if player1/2 are present
extern char player_1_present;
extern char player_2_present;

struct Player* initPlayer(  char a_x,  char a_y, char a_bank, char a_player_num){
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
}

LNode* UpdatePlayer(struct List* objList, LNode* node){
    int player_inpts;
    int old_player_inpts;
    char switch_flip=0;
    char index;
    struct Bullet* blt;
    struct Player* plyr;
    coordinate new_vel_x;
    coordinate new_vel_y;
    coordinate bullet_vel_x;
    coordinate bullet_vel_y;
    coordinate bullet_pos_x;
    coordinate bullet_pos_y;

    if(node){
        if(node->obj_type != OBJ_PLAYER_ID ){
            return NULL;
        }
        plyr = (struct Player*) node->item;

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

/*
  To rotate the player, we cycle through frames and orientations. At frames 0/7, depending on the direction,
   we need to change the orientation to something else.Say that we are on frame 6 (pointed to the right) and we then press right.
   We are now on frame 7, and need to transition from incrementing frames, to decrementing frames (since the next frame to the right is frame 6 FLIPPED across X)
   AT frame 0 and 7, certain FLIP orientations have the same graphical output. Hence, at frames 0 and 7, we just cycle the orientation.
   The order goes NONE-> Y -> BOTH -> X -> NONE. This follows the screen coordinates
   NONE and BOTH increment frame counter, while X and Y decrement. This mapping allows smooth rotation.
*/

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

/*
   Same logic as right, but cycle is reverse, and now NONE and BOTH decrement, but Y and X increment
*/
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

// specifying first frame of each player in sprite sheet
        switch(plyr->player_num){
            case PLYR_ONE_ID:
                plyr->obj->cur_frame = index + PLAYER_ONE_STRT_FRAME;
                break;
            case PLYR_TWO_ID:
                plyr->obj->cur_frame = index + PLAYER_TWO_STRT_FRAME;
                break;
        }

        new_vel_x = gen_x_vel(index,plyr->obj->cur_flip);
        if(player_inpts & INPUT_MASK_B){
            new_vel_x.i = new_vel_x.i;
        }
        else{
            new_vel_x.i = new_vel_x.i>>1;
        }
        new_vel_y = gen_y_vel(index,plyr->obj->cur_flip);

// speed up button
        if(player_inpts & INPUT_MASK_B){
            new_vel_y.i = new_vel_y.i;
        }
        else{
// normal speed  downshifting by 1 since otherwise, too fast
            new_vel_y.i = new_vel_y.i>>1;
        }
        
        if(player_inpts & INPUT_MASK_UP) {
            plyr->obj->v_x.i = new_vel_x.i;
            plyr->obj->v_y.i = new_vel_y.i;
        }

        if(player_inpts & INPUT_MASK_DOWN) {
            plyr->obj->v_x.i = -1*new_vel_x.i;
            plyr->obj->v_y.i = -1*new_vel_y.i;
        }

// shooting button
        if(player_inpts & INPUT_MASK_A) {
            if(plyr->bullet_timer == 0){
                plyr->bullet_timer = BULLET_COOLDOWN;
// bullets move faster than player (gets stuck inside  player otherwise)
                bullet_vel_x.i = new_vel_x.i<<2;
                bullet_vel_y.i = new_vel_y.i<<2;
                bullet_pos_x = plyr->obj->x;
                bullet_pos_y = plyr->obj->y;
                blt = initBullet(bullet_pos_x, bullet_pos_y, bullet_vel_x, bullet_vel_y, BULLET_BANK,plyr->player_num);
                if(blt == NULL){
                    updateObject(plyr->obj);
                    return node->next;
                }
                AddToHead(objList,blt, OBJ_BULLET_ID);
            }
        }

        updateObject(plyr->obj);
        return node->next;
    }
    return NULL;

}
