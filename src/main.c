#include "gametank.h"
#include "drawing_funcs.h"
#include "gen/assets/Bullet.h"
#include "gen/assets/Meteor.h"
#include "gen/assets/Small.h"
#include "object.h"
#include <stdlib.h>

int main () {
    char col = 30, row = 20;
    char dx = 1, dy = 1;
    char cur_frame = 0;
    struct Object* player1;

    init_graphics();

    flip_pages();
    clear_border(0);
    await_draw_queue();
    flip_pages();
    await_draw_queue();
    clear_border(0);

    load_spritesheet(&ASSET__Bullet__Bullet_bmp, 0);
    load_spritesheet(&ASSET__Meteor__Meteor_bmp, 1);
    load_spritesheet(&ASSET__Small__Small_bmp, 2);


    player1 = initObject(  col, row, dx, dy, 16, &ASSET__Small__Small_json, 2);

    while (1) {                                     //  Run forever
        clear_screen(0);
        clear_border(0);
        MoveObject(player1);
        ObjectDraw(player1,0,0);
//        draw_sprite_frame(&ASSET__Bullet__Bullet_json,
//        col, row, 0, 0, 0);
//        draw_sprite(col,row,10,10,0,0,0);
//        draw_box(col, row, 8, 8, 92);
	cursorX = 20;
	cursorY = 30;
        await_draw_queue();
        sleep(1);
        flip_pages();
        ++cur_frame;
    }

  return (0);                                     //  We should never get here!
}
