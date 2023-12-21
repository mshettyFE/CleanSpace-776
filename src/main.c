#include "gametank.h"
#include "drawing_funcs.h"
#include "gen/assets/Small.h"
#include "object.h"
#include "player.h"
#include "constants.h"
#include <stdlib.h>

int main () {
    char col = 30, row = 20;
    char col_two = 60, row_two = 40;
    char dx = 1, dy = 1;
    char cur_frame = 0;
    struct Player* players[2];
    struct Object* test;

    init_graphics();

    flip_pages();
    clear_border(0);
    await_draw_queue();
    flip_pages();
    await_draw_queue();
    clear_border(0);

    load_spritesheet(&ASSET__Small__Small_bmp, SMALL_BANK);

    players[PLYR_ONE_ID] =  initPlayer(  col,  row, 2, PLYR_ONE_ID);
    players[PLYR_TWO_ID] =  initPlayer(  col_two,  row_two, 2, PLYR_TWO_ID);

    while (1) {                                     //  Run forever
        clear_screen(0);
        clear_border(0);
        update_inputs();
        PlayerUpdate(players[0]);
        PlayerUpdate(players[1]);
        MoveObject(players[0]->obj);
        MoveObject(players[1]->obj);
        DrawPlayer(players[0]);
        DrawPlayer(players[1]);
        await_draw_queue();
        sleep(1);
        flip_pages();
        ++cur_frame;
    }

  return (0);                                     //  We should never get here!
}
