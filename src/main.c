#include "random.h"
#include "gametank.h"
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

unsigned int AAAAAAAAAAAAAAAAAA = 2000;
unsigned int BBBBBBBBBBBBBBBBBB = 2000;
unsigned int CCCCCCCCCCCCCCCCCC = 2000;
unsigned int DDDDDDDDDDDDDDDDDD = 1000;
unsigned int OOOOOOOOOOOOOOOOOO = 2000;
unsigned int XXXXXXXXXXXXXXXXXX = 2000;
unsigned int YYYYYYYYYYYYYYYYYY = 2000;
void ZZZZZZZZZZZZZZZZZZZZZZZ(){};

int main () {
    char i = 0;
    char col = 30, row = 20;
    char col_two = 60, row_two = 40;
    char dx = 1, dy = 1;
    char cur_frame = 0;
    coordinate max_speed_squared;
    LNode* t;
    struct List* objList;
    struct List* DeathAnimations;
    
    max_speed_squared = gen_coord(1,0);

//    init_all(objTree, nodes_to_add, nodes_to_remove, DeathAnimations);

    objList = initList();
    DeathAnimations = initList();

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

//    players[PLYR_ONE_ID] =  initPlayer(  col,  row, SMALL_BANK, PLYR_ONE_ID);
//    players[PLYR_TWO_ID] =  initPlayer(  col_two,  row_two, SMALL_BANK, PLYR_TWO_ID);

    AddToHead(objList,initPlayer(  col_two,  row_two, SMALL_BANK, PLYR_TWO_ID),OBJ_PLAYER_ID);
    AddToHead(objList,initPlayer(  col,  row, SMALL_BANK, PLYR_ONE_ID),OBJ_PLAYER_ID);

/*
    t = AddToTail(objList,initPlayer(  90,  90, SMALL_BANK, PLYR_ONE_ID),OBJ_PLAYER_ID);
//    AddNodeToHead(DeathAnimations,initDeathAnim(t));

*/


    for(i=0; i< 1; ++i){
        AddToHead(objList, initMeteor(gen_rand_x, gen_rand_y , SMALL_METEOR), OBJ_METEOR_ID);
        AddToHead(objList, initMeteor(gen_rand_x, gen_rand_y , BIG_METEOR), OBJ_METEOR_ID);
    }




    while (1) {//  Run forever
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
        ++cur_frame;
    }

  return (0);                                     //  We should never get here!
}
