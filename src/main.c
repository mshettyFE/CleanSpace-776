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
#include "object.h"
#include "player.h"
#include "Death.h"
#include "Meteor.h"
#include "coordinate.h"
#include "globals.h"
#include "List.h"
#include <stdlib.h>

unsigned char player_1_present = 0;
unsigned char player_2_present = 0;
unsigned char meteor_present = 0;

#define MAX_METEORS 4

//#define INCLUDE_PLAYERS
#define INCLUDE_METEORS

int main () {
    char i = 0;
    char col = 32, row = 64;
    char col_two = 96, row_two = 64;
    char dx = 1, dy = 1;
    char cur_frame = 0;
    struct List* objList;
    struct List* DeathAnimations;

    objList = initList();
    DeathAnimations = initList();

    init_dynawave();
    init_music();

    flip_pages();
    clear_border(0);
    await_draw_queue();
    flip_pages();
    await_draw_queue();
    clear_border(0);

    load_spritesheet(&ASSET__Death__Death_bmp,DEATH_BANK);
    load_spritesheet(&ASSET__Small__Small_bmp, SMALL_BANK);
    load_spritesheet(&ASSET__Bullets__Bullets_bmp, BULLET_BANK);
    load_spritesheet(&ASSET__Meteor__Meteor_bmp, METEOR_BANK);
    load_spritesheet(&ASSET__SmallMeteor__SmallMeteor_bmp, SMALL_METEOR_BANK);

#ifdef INCLUDE_PLAYERS
    AddToHead(objList,initPlayer(  col_two,  row_two, SMALL_BANK, PLYR_TWO_ID),OBJ_PLAYER_ID);
    AddToHead(objList,initPlayer(  col,  row, SMALL_BANK, PLYR_ONE_ID),OBJ_PLAYER_ID);
#endif
#ifdef INCLUDE_METEORS
    for(i=0; i< MAX_METEORS; ++i){
        AddToHead(objList, initMeteor(gen_rand_x, gen_rand_y , SMALL_METEOR), OBJ_METEOR_ID);
    }
#endif
    while (1) {//  Run forever
        player_1_present  = 0;
        player_2_present  = 0;
        meteor_present = 0;
        clear_screen(0);
        clear_border(1);
        update_inputs();

// iterate through object list. For each item in the object list, update state of object. This includes adding to list(s) of objects to create or delete
// update screen with objects (ignore what needs to be added/deleted for now)
// For each new object to be created, add to the tree
// For each new object to be deleted, remove from the tree
        TraverseList(objList, DeathAnimations);
        TraverseDeathList(DeathAnimations);

        await_draw_queue();
        sleep(1);
        flip_pages();
        tick_music();
        ++cur_frame;

        if(player1_buttons & INPUT_MASK_C || player2_buttons & INPUT_MASK_C){
                ClearList(objList);
                ClearList(DeathAnimations);
                AddToHead(objList,initPlayer(  col_two,  row_two, SMALL_BANK, PLYR_TWO_ID),OBJ_PLAYER_ID);
                AddToHead(objList,initPlayer(  col,  row, SMALL_BANK, PLYR_ONE_ID),OBJ_PLAYER_ID);
                for(i=0; i< MAX_METEORS; ++i){
                    AddToHead(objList, initMeteor(gen_rand_x, gen_rand_y , SMALL_METEOR), OBJ_METEOR_ID);
                }
                continue;
        }

        if(DeathAnimations->size == 0){            
            if(
#ifdef INCLUDE_PLAYERS
                ( !player_1_present && !player_2_present) 
#endif
#ifdef INCLUDE_PLAYERS
#ifdef INCLUDE_METEORS
                ||
#endif
#endif 
#ifdef INCLUDE_METEORS               
              !meteor_present
#endif
                 ){
//            if(  !meteor_present ){
                ClearList(objList);
                ClearList(DeathAnimations);
                AddToHead(objList,initPlayer(  col_two,  row_two, SMALL_BANK, PLYR_TWO_ID),OBJ_PLAYER_ID);
                AddToHead(objList,initPlayer(  col,  row, SMALL_BANK, PLYR_ONE_ID),OBJ_PLAYER_ID);
                for(i=0; i< MAX_METEORS; ++i){
                    AddToHead(objList, initMeteor(gen_rand_x, gen_rand_y , SMALL_METEOR), OBJ_METEOR_ID);
                }
                continue;
            }
        }

    }

  return (0);                                     //  We should never get here!
}
