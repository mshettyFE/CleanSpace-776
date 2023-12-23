#include "gametank.h"
#include "drawing_funcs.h"
#include "gen/assets/Small.h"
#include "gen/assets/Bullets.h"
#include "object.h"
#include "player.h"
#include "globals.h"
#include "Tree.h"
#include <stdlib.h>

unsigned int XXXXXXXXXXXXXXXXXXXXXXXXXXX;
unsigned int YYYYYYYYYYYYYYYYYYYYYYYYYYY;
void ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ(){};

int main () {
    char col = 30, row = 20;
    char col_two = 60, row_two = 40;
    char dx = 1, dy = 1;
    char cur_frame = 0;
    coordinate max_speed_squared;
//    struct Player* players[3];
//    struct Node* temp;
//    struct Node* temp2;
    struct Object* cur_obj;
    struct Head* objTree;
    struct Head* nodes_to_add;
    struct Head* nodes_to_remove;
    struct Head* DeathAnimations;
    max_speed_squared = gen_coord(1,0);

//    init_all(objTree, nodes_to_add, nodes_to_remove, DeathAnimations);

    objTree = initHead();
    nodes_to_remove = initHead();
    nodes_to_add = initHead();
    DeathAnimations = initHead();

    flip_pages();
    clear_border(0);
    await_draw_queue();
    flip_pages();
    await_draw_queue();
    clear_border(0);

    load_spritesheet(&ASSET__Small__Small_bmp, SMALL_BANK);
    load_spritesheet(&ASSET__Bullets__Bullets_bmp, BULLET_BANK);

//    players[PLYR_ONE_ID] =  initPlayer(  col,  row, SMALL_BANK, PLYR_ONE_ID);
//    players[PLYR_TWO_ID] =  initPlayer(  col_two,  row_two, SMALL_BANK, PLYR_TWO_ID);

    insert(objTree,initPlayer(  col,  row, SMALL_BANK, PLYR_ONE_ID),OBJ_PLAYER_ID);
    insert(objTree,initPlayer(  col_two,  row_two, SMALL_BANK, PLYR_TWO_ID),OBJ_PLAYER_ID);

    while (1) {//  Run forever
        clear_screen(0);
        clear_border(0);
        update_inputs();

// iterate through object list. For each item in the object list, update state of object. This includes adding to list(s) of objects to create or delete
// update screen with objects (ignore what needs to be added/deleted for now)
// For each new object to be created, add to the tree
// For each new object to be deleted, remove from the tree

        pollObjects(objTree, objTree, nodes_to_remove );

        await_draw_queue();
        sleep(1);
        flip_pages();
        ++cur_frame;
        XXXXXXXXXXXXXXXXXXXXXXXXXXX = objTree->size;
//        TransferNodes(objTree,nodes_to_add);
        ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ();
    }

  return (0);                                     //  We should never get here!
}