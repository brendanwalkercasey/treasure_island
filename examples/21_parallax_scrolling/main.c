#include <gb/gb.h>
#include "parallax_background_data.h"
#include "parallax_background_map.h"
UINT8 backgroundoffset1x;
UINT8 backgroundoffset2x;
UINT8 backgroundoffset3x;


void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}
void interruptLCD(){
    switch(LYC_REG){
        case 0x00:
            move_bkg(backgroundoffset1x,0);// some value in x, and then no movement in the y-direction
            LYC_REG = 0x35; //set to look for offset 2 (backgroundoffset2x)
            break;
        case 0x35:
            move_bkg(backgroundoffset2x,0);
            LYC_REG = 0x6c;
            break;
        case 0x6c:
            move_bkg(backgroundoffset3x,0);
            LYC_REG = 0x00;
            break;
    }
}
void main(){

    backgroundoffset1x = 0; //clouds
    backgroundoffset2x = 0; //mountains
    backgroundoffset3x = 0; //trees

    set_bkg_data(0, 189, parallax_background_data);
    set_bkg_tiles(0, 0, 32, 18, parallax_background_map);

    STAT_REG = 0x45; //enable LYC=LY interrupt to set a specific line to fire at
    LYC_REG = 0x00; //first line, i.e. zero line

    disable_interrupts();
    add_LCD(interruptLCD);
    enable_interrupts();

    set_interrupts(VBL_IFLAG | LCD_IFLAG);


    SHOW_BKG;
    DISPLAY_ON;

    while(1){
        backgroundoffset1x += 1; //barely moving clouds
        backgroundoffset2x += 2; //slightly moving mountains, still far away
        backgroundoffset3x += 10; //rapidly moving trees
        
        performantdelay(7);
    }
}