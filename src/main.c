#include "gametank.h"
#include "drawing_funcs.h"
#include "gen/assets/Small.h"
#include "object.h"
#include "player.h"
#include "globals.h"
#include "Tree.h"
#include <stdlib.h>

int main () {
    char col = 30, row = 20;
    char col_two = 60, row_two = 40;
    char dx = 1, dy = 1;
    char cur_frame = 0;
    coordinate max_speed_squared;
    struct Player* players[3];
    struct Node* temp;
    struct Node* temp2;
    struct Object* cur_obj;
    struct Head* objTree;
    struct Head* oldNodes;
    struct Head* newNodes;
    struct Head* DeathAnimations;

    counter = 0;

    max_speed_squared = gen_coord(1,0);
    objTree = initHead();
    oldNodes = initHead();
    newNodes = initHead();
    DeathAnimations = initHead();

    init_graphics();

    flip_pages();
    clear_border(0);
    await_draw_queue();
    flip_pages();
    await_draw_queue();
    clear_border(0);

    load_spritesheet(&ASSET__Small__Small_bmp, SMALL_BANK);

    players[PLYR_ONE_ID] =  initPlayer(  col,  row, SMALL_BANK, PLYR_ONE_ID);
    players[PLYR_TWO_ID] =  initPlayer(  col_two,  row_two, SMALL_BANK, PLYR_TWO_ID);
    players[2] =            initPlayer( 45, 45, SMALL_BANK, PLYR_ONE_ID);

    insert(objTree,players[PLYR_ONE_ID],OBJ_PLAYER_ID);
    insert(objTree,players[PLYR_TWO_ID],OBJ_PLAYER_ID);

    while (1) {               //  Run forever
        clear_screen(0);
        clear_border(0);
        update_inputs();

// iterate through object list. For each item in the object list, update state of object. This includes adding to list(s) of objects to create or delete
// update screen with objects (ignore what needs to be added/deleted for now)
// For each new object to be created, add to the tree
// For each new object to be deleted, remove from the tree

        temp = search(objTree, players[PLYR_ONE_ID], OBJ_PLAYER_ID);
        temp2 = search(objTree, players[PLYR_TWO_ID], OBJ_PLAYER_ID);

        if(temp != NULL){
          UpdatePlayer((struct Player*)temp->obj, NULL, NULL);
        }

        if(temp2 != NULL){
          UpdatePlayer((struct Player*)temp2->obj, NULL, NULL);
        }

        await_draw_queue();
        sleep(1);
        flip_pages();
        ++cur_frame;
    }

  return (0);                                     //  We should never get here!
}