# treasure_island

## Chris's Instructions
You can run the executable from whatever directory you download it
from using the following.

> gbsc.exe size=8x8 input.jpg

png also work. If you don't specify a size it will just use the input
image size. You can run it for multiple input jpgs in the following
manner

> gbsc.exe size=8x8 input1.jpg input2.jpg size=16x32 input3.jpg input4.png

The script will generate .c and .files named after the input files in
its current directory.

To reference these files in main.c you should do the following using
input1.jpg as an example.

#include "input1.c"
set_sprite_data(0, 1, input1);

## Resources
- Pixel art (256 value (8-bit) background maps, and associated tile maps) [https://www.systemoflevers.com/image-to-gb/]