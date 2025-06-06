#include <gb/gb.h>
//#include <gb/hardware.h>
//#include <rand.h>
#include <stdio.h>
//#include "admiral_benbow_outside.h"
#include "admiral_benbow_outside_62_tiles.h"
//#include "all_tiles.h"
#include "all_tiles_62_tiles.h"

// ******** temp (testing different data) *********
//#include "windowmap.c"
#include "guy.h"
#include "test_char.h"
#include "examplesprite.h"
#include "BackgroundData.h"
#include "BackgroundMap.h"

// ******** temp *********

//use this custom delay function, instead of built in gbdk function
// (less CPU spikes than built in gbdk funciton)
void performantdelay(uint8_t numloops){
    uint8_t i;
    for(i = 0; i< numloops; i++){
        wait_vbl_done();
    }
}
void init(){

    set_bkg_data(0,62,all_tiles_62_tiles); // 7 tiles into background
    set_bkg_tiles(0,0,90,90,adm_ben_out_62_tiles); // coords (0,0) and 90 tiles wide, 90 tiles high
    //set_win_tiles(0,0,5,1,windowmap);

    set_sprite_data(0,2,guy);
    set_sprite_tile(0,0);
    move_sprite(0, 88, 78); // orig
    //move_sprite(0,22,78);
}

void update_switches(){

    NR52_REG = 0x8F; // sound on
    NR51_REG = 0x11; // sound channels on
    NR50_REG = 0x77; // volume max

    HIDE_WIN;  //not sure what this does
    SHOW_SPRITES;
    SHOW_BKG;
    

    //DISPLAY_ON; // display on
}

void check_input(){

while(1){
        switch(joypad()){
            case J_LEFT:
                scroll_sprite(4,-1,0);
                break;
            case J_RIGHT:
                scroll_sprite(4,1,0);
                break;
            case J_UP:
                scroll_sprite(4,0,-1);
                set_sprite_prop(4,get_sprite_prop(4) & ~S_PRIORITY); // when up key is pressed, bring sprite to front
                break;
            case J_DOWN:
                scroll_sprite(4,0,1);
                break;

        }
        performantdelay(2);
    }
/*

    switch(joypad()){
            case J_LEFT: 
                scroll_sprite(0,-1,0);
                break;
            case J_RIGHT: 
                scroll_sprite(0,1,0);
                break;  
            case J_UP: 
                scroll_sprite(0,0,-1);
                break; 
            case J_DOWN: 
                scroll_sprite(0,0,1);
                break;                                                   
        }

*/

}

void main(){

    update_switches();
    init();
    
    //scrolling the background
    while(1){
        scroll_bkg(1,0);
        check_input();
        delay(100);
    }
}


