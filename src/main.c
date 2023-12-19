#include "gametank.h"
#include "drawing_funcs.h"
#include "gen/assets/Bullet.h"
#include <stdlib.h>

int main () {
    char col = 30, row = 20;
    int dx = 1, dy = 1;
    char cur_frame = 0;

    init_graphics();

    flip_pages();
    clear_border(0);
    await_draw_queue();
    flip_pages();
    await_draw_queue();
    clear_border(0);

    load_spritesheet(&ASSET__Bullet__Bullet_bmp, 0);


    while (1) {                                     //  Run forever
        clear_screen(0);
        clear_border(0);
        draw_sprite_frame(&ASSET__Bullet__Bullet_json,
        col, row, 0, 0, 0);
//        draw_sprite(col,row,10,10,0,0,0);
        if(cur_frame == 7){
            cur_frame = 0;
        }
//        draw_box(col, row, 8, 8, 92);
        col += dx;
        row += dy;
        if(col == 1) {
            dx = 1;
        } else if(col == 119) {
            dx = -1;
        }
        if(row == 8) {
            dy = 1;
        } else if(row == 112) {
            dy = -1;
        }
	cursorX = 20;
	cursorY = 30;
        await_draw_queue();
        sleep(1);
        flip_pages();
        ++cur_frame;
        
    }

  return (0);                                     //  We should never get here!
}
