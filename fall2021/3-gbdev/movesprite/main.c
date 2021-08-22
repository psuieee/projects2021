#include <gb/gb.h>
#include <stdint.h>
#include "smiley.h"


void main(void)
{
    int x = 50;
    int y = 50;

    SPRITES_8x8;
    set_sprite_data(0, 8, Smiley);
    set_sprite_tile(0, 0);
    move_sprite(0, x, y);
    SHOW_SPRITES;

    // Loop forever
    while(1) {


		// Game main loop processing goes here
        if(joypad() & J_RIGHT) {
            x++;
            move_sprite(0, x, y);
            delay(10);
        }
        if(joypad() & J_LEFT) {
            x--;
            move_sprite(0, x, y);
            delay(10);
        }
        if(joypad() & J_UP) {
            y--;
            move_sprite(0, x, y);
            delay(10);
        }
        if(joypad() & J_DOWN) {
            y++;
            move_sprite(0, x, y);
            delay(10);
        }

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
