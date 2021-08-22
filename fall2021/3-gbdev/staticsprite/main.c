#include <gb/gb.h>
#include <stdint.h>
#include "smiley.h"


void main(void)
{
    const int x = 50;
    const int y = 50;

    SPRITES_8x8;
    set_sprite_data(0, 8, Smiley);
    set_sprite_tile(0, 0);
    move_sprite(0, x, y);
    SHOW_SPRITES;

    // Loop forever
    while(1) {


		// Game main loop processing goes here


		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
