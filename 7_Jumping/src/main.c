#include <gb/gb.h>

// Player INFO
#define PLAYER_SPRITE 0

struct SpritePos
{
    INT8 _x;
    INT8 _y;
} player;

unsigned char Smile[] =
{
  0x3C,0x3C,0x7E,0x42,0xFF,0xA5,0xFF,0x81,
  0xFF,0xA5,0xFF,0x99,0x7E,0x42,0x3C,0x3C,
  0x3C,0x3C,0x7E,0x42,0xFF,0xA5,0xFF,0x81,
  0xFF,0x81,0xFF,0xBD,0x7E,0x42,0x3C,0x3C
};

void performantdelay(UINT8 numFrames) {
    UINT8 i;
    for (i = 0; i < numFrames; i++)
    {
        wait_vbl_done();
    }    
}


void playerMovement() {
    UINT8 input = joypad();

    if (input & J_LEFT)
    {
        player._x -= 2;
        move_sprite(PLAYER_SPRITE, player._x, player._y);
    }

    if (input & J_RIGHT)
    {
        player._x += 2;
        move_sprite(PLAYER_SPRITE, player._x, player._y);
    }
}

void main(){
    set_sprite_data(0, 8, Smile);
    set_sprite_tile(PLAYER_SPRITE,0);

    // Set player start location
    player._x = 10;
    player._y = 100;

    move_sprite(PLAYER_SPRITE, player._x,player._y);

    DISPLAY_ON;
    SHOW_SPRITES;

    while (1)
    {
        playerMovement();
        performantdelay(2);
    }
    
}
