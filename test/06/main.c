#include <gb/gb.h>
#include <stdio.h>
#include "admiral_benbow_outside_62_tiles.h"
#include "all_tiles_62_tiles.h"
#include "jim_hawkins.h"
//#include "game_char.c"
//#include "game_char.h"

// struct for "mega-sprite" (i.e. pieces of Jim Hawkins)
struct game_char {
    UBYTE spriteids[6];
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;   
};

// call instance of struct, called jimbo (i.e. Jim Hawkins)
struct game_char jimbo;

UBYTE spritesize = 8;

//use this custom delay function, instead of built in gbdk function
// (less CPU spikes than built in gbdk funciton)
void performantdelay(uint8_t numloops){
    uint8_t i;
    for(i = 0; i< numloops; i++){
        wait_vbl_done();
    }
}

void move_game_char(struct game_char* character, uint8_t x, uint8_t y){
    move_sprite(character->spriteids[0], x, y);
    move_sprite(character->spriteids[1], x + spritesize, y);
    move_sprite(character->spriteids[2], x, y + spritesize);
    move_sprite(character->spriteids[3], x + spritesize, y + spritesize);
    move_sprite(character->spriteids[4], x , y + spritesize + spritesize);
    move_sprite(character->spriteids[5], x + spritesize, y + spritesize + spritesize);
}

// assemble Jim
void setupGameChar() {
    jimbo.x = 80;
    jimbo.y = 130;
    jimbo.width = 16;
    jimbo.height = 24;

    //load sprites to "build" Jim
    set_sprite_tile(0,0);
    jimbo.spriteids[0] = 0;
    set_sprite_tile(1,1);
    jimbo.spriteids[1] = 1;
    set_sprite_tile(2,2);
    jimbo.spriteids[2] = 2;
    set_sprite_tile(3,3);
    jimbo.spriteids[3] = 3;
    set_sprite_tile(4,4);
    jimbo.spriteids[4] = 4;
    set_sprite_tile(5,5);
    jimbo.spriteids[5] = 5;

    move_game_char(&jimbo, jimbo.x, jimbo.y);
}


void init(){

    set_bkg_data(0,62,all_tiles_62_tiles); // 62 tiles into background
    set_bkg_tiles(0,0,90,90,adm_ben_out_62_tiles); // coords (0,0) and 90 tiles wide, 90 tiles high
    //set_win_tiles(0,0,5,1,windowmap);

    setupGameChar();
    set_sprite_data(0,8,jim_hawkins);
    set_sprite_tile(0,0);
    //move_sprite(0, 88, 78);
}

void update_switches(){

    NR52_REG = 0x8F; // sound on
    NR51_REG = 0x11; // sound channels on
    NR50_REG = 0x77; // volume max

    SHOW_SPRITES;
    SHOW_BKG;
    
    DISPLAY_ON; // display on
}

void check_input(){
    
    while(1){
        if(joypad() & J_LEFT){
            jimbo.x -= 2;
            move_game_char(&jimbo, jimbo.x, jimbo.y);
        }
        if(joypad() & J_RIGHT){
            jimbo.x += 2;
            move_game_char(&jimbo, jimbo.x, jimbo.y);
        }
        if(joypad() & J_DOWN){
            jimbo.y += 2;
            move_game_char(&jimbo, jimbo.x, jimbo.y);
        }
        if(joypad() & J_UP){
            jimbo.y -= 2;
            move_game_char(&jimbo, jimbo.x, jimbo.y);
        }
        performantdelay(3);
    }


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


