#include <gb/gb.h>
#include "test_char.h"
#include "test_map.h"

void main(){
    set_bkg_data(0,7,guy);
    set_bkg_tiles(0,0,40,18,map);

    SHOW_BKG;
    DISPLAY_ON;

    //scrolling the background
    while(1){
        scroll_bkg(1,0);
        delay(100);
    }
}