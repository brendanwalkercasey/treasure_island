#include <gb/gb.h>
#include <stdio.h>
#include "MazeSprites.c"
#include "MazeMap.c"
#include "Snail.c"

const car blankmap[1] = {0x00};
UINT8 playerlocation[2];
UBYTE debug = 0, haskey = 0, game_run = 0;

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void init_gfx() {
    // Load Background tiles and then map
    set_bkg_data(0, 4, MazeSprites);
    set_bkg_tiles(0, 0, 20, 18, MazeMap);
    // Load Sprite data and tile numbers
    set_sprite_data(0, 1, Snail);
    set_sprite_tile(0,0);

    playerlocation[0] = 16;
    playerlocation[1] = 24;

    move_sprite(0, playerlocation[0], playerlocation[1]);

	// Turn the background map on to make it visible
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}

UBYTE can_player_move(UINT8 newplayerx, UINT8 newplayery){
    UINT16 indexTLx, indexTLy, tileindexTL;
    UBYTE result;

    indexTLx = (newplayerx - 8) / 8;
    indexTLy = (newplayery - 16) / 8;
    tileindexTL = 20 * (indexTLy + indexTLx);

    if(debug){
        printf("newplayerx: %u, newplayery: %u \n", (UINT16)(newplayerx), (UINT16)(newplayery));
        printf("indexTLX: %u, indexTLy: %u, tileindexTL: %u\n", (UINT16)indexTLx, (UINT16)indexTLy, (UINT16)tileindexTL);
    }

    result = MazeMap[tileindexTL] == blankmap[0];

    if(tileindexTL == 321){
        //grab key
        set_bkg_tiles(1,16,1,1,blankmap);
        haskey = 1;
        result = 1;
    }
    if(tileindexTL == 263 && haskey){
        //door open
        set_bkg_tiles(3,13,1,1,blankmap);
        result = 1;
    }
    else if(tileindexTL == 340){
        //end game
        game_run = 0;
        HIDE_SPRITES;
        printf("\n \n *********\n YOU WIN! \n *********\n \n \n");
        result = 1;
    }
    return result;
}

void animatesprite(UINT8 spriteindex, INT8 movex, INT8 movey){
    //tbd
}

void init_joypad() {

    if(joypad() & J_A){
        debug = 1;
    }        
        if(joypad() & J_LEFT){
            if(canplayermove(playerlocation[0]-8,playerlocation[1])){
                playerlocation[0] -= 8;
                animatesprite(0,-8,0);
            }
        }
        else if(joypad() & J_RIGHT){
            if(canplayermove(playerlocation[0]+8,playerlocation[1])){            
                playerlocation[0] += 8;
                animatesprite(0,8,0);
            }
        }
        else if(joypad() & J_UP){
            if(canplayermove(playerlocation[0],playerlocation[1]-8)){
                playerlocation[1] -= 8;
                animatesprite(0,0,-8);
            }
        }
        else if(joypad() & J_DOWN){
            if(canplayermove(playerlocation[0],playerlocation[1]+8)){
                playerlocation[1] += 8;
                animatesprite(0,0,8);
            }
        }
    performantdelay(6);
}



void main(void) {
	
    //initialize graphics
    init_gfx();

    game_run = 1;
    // Loop game
    while(game_run) {

		// Game main loop processing
        init_joypad();

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
