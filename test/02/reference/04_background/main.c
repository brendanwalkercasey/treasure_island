#include <gb/gb.h>
#include "simplebackground.h"
#include "simplebackgroundmap.h"

void main(){
    set_bkg_data(0,7,backgroundtiles);
    set_bkg_tiles(0,0,40,18,backgroundmap);

    SHOW_BKG;
    DISPLAY_ON;

    //scrolling the background
    while(1){
        scroll_bkg(1,0);
        delay(100);
    }
}