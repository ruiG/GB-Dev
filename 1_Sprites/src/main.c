#include <gb/gb.h>
#include "smile.h"

void main()
{
    UINT8 spriteIndex = 0;
    UINT8 a = 0;
    UINT8 c = 0;

    set_sprite_data(0, 2, Smile);
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;

    while (1)
    {
        c += 1;
        a += 1;
        if (spriteIndex == 0)
        {
            spriteIndex = 1;
        }
        else
        {
            spriteIndex = 0;
        }
        set_sprite_tile(0, spriteIndex);
        delay(1000);
        scroll_sprite(0,10,0);
    }
}