#include <stdlib.h>
#include "object.h"
#include "player.h"
#include "input.h"
#include "drawing_funcs.h"
#include "coordinate.h"

#include <stdlib.h>

#include "gen/assets/Small.h"

signed int cur_speed = 0;

struct Player* initPlayer(  char a_x,  char a_y, char a_bank, char a_player_num){
    struct Player* plyr = malloc(sizeof(struct Player));
    plyr->player_num = a_player_num;
    switch (plyr->player_num)
    {
    case PLYR_ONE_ID:
        plyr->obj = initObject( a_x, a_y, 0, 0, 4, &ASSET__Small__Small_json, a_bank, PLAYER_ONE_STRT_FRAME, SPRITE_FLIP_NONE);
        break;
    case PLYR_TWO_ID:
        plyr->obj = initObject( a_x, a_y, 0, 0, 4, &ASSET__Small__Small_json, a_bank, PLAYER_TWO_STRT_FRAME, SPRITE_FLIP_NONE);
        break;    
    default:
        break;
    }
/*
    if(plyr->player_num == PLYR_ONE_ID)
    plyr->obj = initObject( a_x, a_y, 0, 0, 4, &ASSET__Small__Small_json, a_bank);
    if(plyr->player_num == PLYR_ONE_ID)
    {
        plyr->obj->cur_frame = PLAYER_ONE_STRT_FRAME;
    }
    else{
        plyr->obj->cur_frame = PLAYER_TWO_STRT_FRAME;
    }
    plyr->obj->cur_flip = SPRITE_FLIP_NONE;
*/
    return plyr;
}

void freePlayer(struct Player* plyr){
    if(plyr == NULL){
        return;
    }
    freeObj(plyr->obj);
    free(plyr);
}

void UpdatePlayer(struct Player* plyr, struct  Head* new_nodes, struct Head* expired_nodes){
    int player_inpts;
    char switch_flip=0;
    char index;
    coordinate acceleration_x;
    coordinate acceleration_y;

    switch (plyr->player_num)
    {
      case PLYR_ONE_ID:
        player_inpts = player1_buttons;
        index = plyr->obj->cur_frame - PLAYER_ONE_STRT_FRAME;
        break;
      case PLYR_TWO_ID:
        player_inpts = player2_buttons;
        index = plyr->obj->cur_frame - PLAYER_TWO_STRT_FRAME;
        break;    
    }

    if(player_inpts & INPUT_MASK_RIGHT){
        switch (plyr->obj->cur_flip)
        {
            case SPRITE_FLIP_NONE:
                index += 1;
                if(index==7){
                    plyr->obj->cur_flip = SPRITE_FLIP_Y;
                    break;
                }
                break;

            case SPRITE_FLIP_Y:
                index -= 1;
                if(index==0){
                    plyr->obj->cur_flip = SPRITE_FLIP_BOTH;
                    break;
                }
                break;
            case SPRITE_FLIP_BOTH:
                index += 1;
                if(index==7){
                    plyr->obj->cur_flip = SPRITE_FLIP_X;
                    break;
                }
                break;        
            case SPRITE_FLIP_X:
                index -= 1;
                if(index==0){
                    plyr->obj->cur_flip = SPRITE_FLIP_NONE;
                    break;
                }
                break;
        }
        switch(plyr->player_num){
            case PLYR_ONE_ID:
                plyr->obj->cur_frame = index + PLAYER_ONE_STRT_FRAME;
                break;
            case PLYR_TWO_ID:
                plyr->obj->cur_frame = index + PLAYER_TWO_STRT_FRAME;
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
        switch(plyr->player_num){
            case PLYR_ONE_ID:
                plyr->obj->cur_frame = index + PLAYER_ONE_STRT_FRAME;
                break;
            case PLYR_TWO_ID:
                plyr->obj->cur_frame = index + PLAYER_TWO_STRT_FRAME;
                break;
        }
    }

    acceleration_x = gen_x_accel(index,plyr->obj->cur_flip);
    acceleration_y = gen_y_accel(index,plyr->obj->cur_flip);

    cur_speed = plyr->obj->v_y.i;
    
    if(player_inpts & INPUT_MASK_UP) {
          plyr->obj->v_x.i = acceleration_x.i;
          plyr->obj->v_y.i = acceleration_y.i;
    }

    if(player_inpts & INPUT_MASK_DOWN) {
          plyr->obj->v_x.i = -1*acceleration_x.i;
          plyr->obj->v_y.i = -1*acceleration_y.i;
/*
        char sign_change_x, sign_change_y;
        coordinate old_vx, old_vy;
        old_vx = plyr->obj->v_x;
        old_vy = plyr->obj->v_y;
        plyr->obj->v_x.i -= acceleration_x.i;
        plyr->obj->v_y.i -= acceleration_y.i;
        sign_change_x = old_vx.i < 0 && plyr->obj->v_x.i >= 0 || old_vx.i >= 0 && plyr->obj->v_x.i < 0; 
        sign_change_y = old_vy.i < 0 && plyr->obj->v_y.i >= 0 || old_vy.i >= 0 && plyr->obj->v_y.i < 0; 
        if (sign_change_x || sign_change_y) {
            plyr->obj->v_x.i -= acceleration_x.i;
            plyr->obj->v_y.i -= acceleration_y.i;
        }
*/
    }

    updateObject(plyr->obj);

}