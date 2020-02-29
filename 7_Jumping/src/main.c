#include <gb/gb.h>

#define PLAYER_SPRITE 0
#define GRAVITY 2 // positive because Y is downwards
#define TERMINAL_VEL 8
#define PLAYER_JUMP_SPEED 15 // absolute initial jump speed
#define FLOOR SCREENHEIGHT

struct SpriteProps
{
    INT8 _x;      // x position
    INT8 _y;      // y position
    INT8 _sy;     // y speed
    BYTE jumping; // is jumping
    BYTE startJump;
} player;

unsigned char Smile[] =
    {
        0x3C, 0x3C, 0x7E, 0x42, 0xFF, 0xA5, 0xFF, 0x81,
        0xFF, 0xA5, 0xFF, 0x99, 0x7E, 0x42, 0x3C, 0x3C,
        0x3C, 0x3C, 0x7E, 0x42, 0xFF, 0xA5, 0xFF, 0x81,
        0xFF, 0x81, 0xFF, 0xBD, 0x7E, 0x42, 0x3C, 0x3C};

void performantdelay(UINT8 numFrames)
{
    UINT8 i;
    for (i = 0; i < numFrames; i++)
    {
        wait_vbl_done();
    }
}

UINT8 abs_8(INT8 number)
{
    BYTE mask = (number >> 7);
    return ((number ^ mask) - mask);
}

BYTE hitFloor(INT8 next_y)
{
    if (next_y >= FLOOR)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void animations()
{
    // initiate the jump
    if (player.startJump == 1)
    {
        player._sy = -PLAYER_JUMP_SPEED;
        player.startJump = 0;
        player.jumping = 1;
    }

    if (player.jumping == 1)
    {
        INT8 next_y;

        if (player._sy <= TERMINAL_VEL) // caution not ABS val!
        {
            player._sy += GRAVITY;
        }

        // effect of velocity
        next_y = player._y + player._sy;

        if (hitFloor(next_y))
        {
            player.jumping = 0; // jump stop
            player._sy = 0;     // remove vertical vel
            player._y = FLOOR;  // set Y as floor height
        }
        else
        {
            player._y = next_y;
        }
    }
}

void playerInputs()
{
    UINT8 input = joypad();

    if (input & J_A && player.jumping == 0)
    {
        player.startJump = 1;
    }

    if (input & J_LEFT)
    {
        player._x -= 2;
    }

    if (input & J_RIGHT)
    {
        player._x += 2;
    }
}

void moveSprites()
{
    move_sprite(PLAYER_SPRITE, player._x, player._y);
}

void main()
{
    set_sprite_data(0, 8, Smile);
    set_sprite_tile(PLAYER_SPRITE, 0);

    // Set player start location
    player._x = 10;
    player._y = 0;
    player.jumping = 1;

    move_sprite(PLAYER_SPRITE, player._x, player._y);

    DISPLAY_ON;
    SHOW_SPRITES;

    while (1)
    {
        playerInputs();
        animations();
        moveSprites();
        performantdelay(2);
    }
}
