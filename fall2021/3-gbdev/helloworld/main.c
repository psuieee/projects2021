#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

void main(void)
{   
    printf("Hello World");
    
    // Loop forever
    while(1) {


		// Game main loop processing goes here

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
