#include "random.h"
#include "gametank.h"
#include "dynawave.h"
#include "music.h"
#include "drawing_funcs.h"
#include "gen/assets/Small.h"
#include "gen/assets/Bullets.h"
#include "gen/assets/Death.h"
#include "gen/assets/Meteor.h"
#include "gen/assets/SmallMeteor.h"
#include "gen/assets/Background.h"
#include "gen/assets/font.h"
#include "object.h"
#include "player.h"
#include "Death.h"
#include "Meteor.h"
#include "coordinate.h"
#include "globals.h"
#include "List.h"
#include "banking.h"
#include "gt/feature/text/text.h"
#include <stdlib.h>

// flags to check if these objects exist in scene
char player_1_present = 0;
char player_2_present = 0;
char meteor_present = 0;

char paused = 0;


void GenField(struct List* objList, struct List* death){
    char i = 0;
// initial position of player 1
    char col = 32, row = 64;
// initial position of player 2
    char col_two = 96, row_two = 64;
    AddToHead(objList,initPlayer(  col_two,  row_two, SMALL_BANK, PLYR_TWO_ID),OBJ_PLAYER_ID);
    AddToHead(objList,initPlayer(  col,  row, SMALL_BANK, PLYR_ONE_ID),OBJ_PLAYER_ID);
    for(i=0; i< rnd_range(5,15); ++i){
        AddToHead(objList, initMeteor(gen_rand_x, gen_rand_y , SMALL_METEOR), OBJ_METEOR_ID);
    }
}

void displayText(const char* str){
    change_rom_bank(FONT_BANK);
// clear both buffers of everything
    flip_pages();
    clear_screen(0);
    clear_border(0);
    await_draw_queue();
    flip_pages();
    clear_screen(0);
    clear_border(0);
    await_draw_queue();
    flip_pages();
    while(1){
        cursorX = 0;
        cursorY = 12;
//        draw_sprite_frame(&ASSET__Background__background_json, 127,127,0,0,BACK_BANK);
//        print_text(str);
        print(str);
        update_inputs();
        if( ((player1_buttons & INPUT_MASK_START & ~player1_old_buttons ) ) ||
            ((player2_buttons & INPUT_MASK_START & ~player2_old_buttons )) ){
            break;
        }
        sleep(1);
    }
}

int main () {
    char cur_frame = 0;
    struct List* objList;
    struct List* DeathAnimations;

    objList = initList();
    DeathAnimations = initList();

//    init_dynawave();
//    init_music();

    load_font(FONT_BANK);
    load_spritesheet(&ASSET__Death__Death_bmp,DEATH_BANK);
    load_spritesheet(&ASSET__Small__Small_bmp, SMALL_BANK);
    load_spritesheet(&ASSET__Bullets__Bullets_bmp, BULLET_BANK);
    load_spritesheet(&ASSET__Meteor__Meteor_bmp, METEOR_BANK);
    load_spritesheet(&ASSET__SmallMeteor__SmallMeteor_bmp, SMALL_METEOR_BANK);
    load_spritesheet(&ASSET__Background__background_bmp, BACK_BANK);

    GenField(objList, DeathAnimations);


    displayText("team up to clean up outer space\n\n""pad to move\n""a to fire\n"
        "b to go brrr\n""c to reset\n""strt to pause\n\n""try not to kill each other\n\n""hit strt to play\n");

    while (1) {//  Run forever
        player_1_present  = 0;
        player_2_present  = 0;
        meteor_present = 0;
        clear_screen(0);
        clear_border(1);
        update_inputs();
        TraverseList(objList, DeathAnimations);
        TraverseDeathList(DeathAnimations);
        if(player1_buttons & INPUT_MASK_C || player2_buttons & INPUT_MASK_C){
                ClearList(objList);
                ClearList(DeathAnimations);
                GenField(objList, DeathAnimations);
                continue;
        }

        if( (player_1_present && (player1_buttons & INPUT_MASK_START & ~player1_old_buttons ) ) ||
         (player_2_present &&  (player2_buttons & INPUT_MASK_START & ~player2_old_buttons )) ){
            paused = ~paused;
            continue;
        }


        if(DeathAnimations->size == 0){
            if(   ( !player_1_present && !player_2_present)  ||  !meteor_present){
                ClearList(objList);
                ClearList(DeathAnimations);
                GenField(objList, DeathAnimations);
                if( !player_1_present && !player_2_present){
                    displayText("you both died\n\nhit start to\ntry again");
                    continue;
                }
                if(!meteor_present){
                    displayText("you both cleared\neverything\n\nhit start to\nclean up more\nspace junk");
                    continue;
                }
            }
        }
        await_draw_queue();
        sleep(1);
        flip_pages();
//        tick_music();
        ++cur_frame;
    }

  return (0);
}
