#include <gb/gb.h>
#include "backgroundTiles.h"
#include "backgroundmap.h"

void main()
{
    set_bkg_data(0, 7, backgroundTiles);
    set_bkg_tiles(0, 0, 40, 18, backgroundMap);

    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
        scroll_bkg(1, 0);
        delay(100);
    }
}