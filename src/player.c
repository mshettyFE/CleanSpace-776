#include <stdlib.h>
#include "object.h"
#include "player.h"
#include "input.h"
#include "drawing_funcs.h"
#include "coordinate.h"

#include <stdlib.h>

#include "gen/assets/Small.h"

struct Player* initPlayer(  char a_x,  char a_y, char a_bank, char a_player_num){
    struct Player* plyr = malloc(sizeof(struct Player));
    plyr->obj = initObject( a_x, a_y, 0, 0, 4, &ASSET__Small__Small_json, a_bank);
    plyr->player_num = a_player_num;
    if(plyr->player_num == PLYR_ONE_ID)
    {
        plyr->cur_frame = PLAYER_ONE_STRT_FRAME;
        plyr->plyr_index = 255;
    }
    else{
        plyr->cur_frame = PLAYER_TWO_STRT_FRAME;
        plyr->plyr_index = 255;
    }
    plyr->cur_flip = SPRITE_FLIP_NONE;
    return plyr;
}

void DrawPlayer(struct Player* plyr){
    ObjectDraw(plyr->obj, plyr->cur_frame, plyr->cur_flip);
}




void PlayerUpdate(struct Player* plyr, const coordinate max_speed_squared){
    int player_inpts;
    char switch_flip=0;
    char index;
    coordinate acceleration_x;
    coordinate acceleration_y;

    switch (plyr->player_num)
    {
      case PLYR_ONE_ID:
        player_inpts = player1_buttons;
        index = plyr->cur_frame - PLAYER_ONE_STRT_FRAME;
        break;
      case PLYR_TWO_ID:
        player_inpts = player2_buttons;
        index = plyr->cur_frame - PLAYER_TWO_STRT_FRAME;
        break;    
    }

    if(player_inpts & INPUT_MASK_RIGHT){
        switch (plyr->cur_flip)
        {
            case SPRITE_FLIP_NONE:
                index += 1;
                if(index==7){
                    plyr->cur_flip = SPRITE_FLIP_Y;
                    break;
                }
                break;

            case SPRITE_FLIP_Y:
                index -= 1;
                if(index==0){
                    plyr->cur_flip = SPRITE_FLIP_BOTH;
                    break;
                }
                break;
            case SPRITE_FLIP_BOTH:
                index += 1;
                if(index==7){
                    plyr->cur_flip = SPRITE_FLIP_X;
                    break;
                }
                break;        
            case SPRITE_FLIP_X:
                index -= 1;
                if(index==0){
                    plyr->cur_flip = SPRITE_FLIP_NONE;
                    break;
                }
                break;
        }
        switch(plyr->player_num){
            case PLYR_ONE_ID:
                plyr->cur_frame = index + PLAYER_ONE_STRT_FRAME;
                break;
            case PLYR_TWO_ID:
                plyr->cur_frame = index + PLAYER_TWO_STRT_FRAME;
                break;
        }
    }
    if(player_inpts & INPUT_MASK_LEFT){
        switch (plyr->cur_flip)
        {
            case SPRITE_FLIP_NONE:
                if(index==0){
                    plyr->cur_flip = SPRITE_FLIP_X;
                    break;
                }
                index -= 1;
                break;

            case SPRITE_FLIP_Y:
                if(index==7){
                    plyr->cur_flip = SPRITE_FLIP_NONE;
                    break;
                }
                index += 1;
                break;
            case SPRITE_FLIP_BOTH:
                if(index==0){
                    plyr->cur_flip = SPRITE_FLIP_Y;
                    break;
                }
                index -= 1;
                break;        
            case SPRITE_FLIP_X:
                if(index==7){
                    plyr->cur_flip = SPRITE_FLIP_BOTH;
                    break;
                }
                index += 1;
                break;
        }
        switch(plyr->player_num){
            case PLYR_ONE_ID:
                plyr->cur_frame = index + PLAYER_ONE_STRT_FRAME;
                break;
            case PLYR_TWO_ID:
                plyr->cur_frame = index + PLAYER_TWO_STRT_FRAME;
                break;
        }
    }

    acceleration_x = gen_x_accel(index,plyr->cur_flip);
    acceleration_y = gen_y_accel(index,plyr->cur_flip);

    if(player_inpts & INPUT_MASK_UP) {
        plyr->obj->v_x = acceleration_x;
        plyr->obj->v_y = acceleration_y;   
    }

}