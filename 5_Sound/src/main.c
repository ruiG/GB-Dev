#include <gb/gb.h>

void main(){

    NR52_REG = 0x80; // 1000 0000 - turn on the sound
    NR50_REG = 0x77; // 0111 0111‬ - left and right channel volume to max
    NR51_REG = 0xFF; // 1111 1111 - select which channels - all of them for both channels

    while (1)
    {
        UBYTE joypad_state = joypad();

        if(joypad_state) {

            // channel 1 register 0, frequency sweep settings
            // 7        unused
            // 6-4      Sweep update rate (0 is off)
            // 3        Sweep direction (1 decrease, 0 increase)
            // 2-0      Sweep RTShift ammount (0 is off)
            // 0001 0110 is 0x16, sweep time is 1, direction is increase, shift ammount per step 110 (6 decimal)
            NR10_REG = 0x16;

            // channel 1 register 1, Wave pattern duty and sound length
            // 7-6      duty cycle 0-3 (12.5%, 25%, 50%, 75%)
            // 5-0      length of sound (higher is shorter)
            // 0100 0000 is 0x40, duty cycle 1, long wave
            NR11_REG = 0x40;

            // channel 1 register 2, Volume envelope
            // 7-4      initial channel volume
            // 3        sweep direction (0 down, 1 up)
            // 2-0      length of each step in sweep (0 is off)
            // 0111 0011 is 0x73, volume 7, sweep down, step 3
            NR12_REG = 0x73;

            // channel 1 register 3, Frequency LSbs 
            // 7-0      8 least significant bits of freequency
            NR13_REG = 0x00;

            // channel 1 register 3, Playback and frequency MSbs
            // 7        Initialize (trigger channel start) Write only
            // 6        Consecutive select/length counter enable (R/W) When "0", regardless of the length of data on the NR11 register, sound can be produced consecutively.  When "1", sound is generated during the time period set by the length data contained in register NR11.  After the sound is ouput, the Sound 1 ON flag, at bit 0 of register NR52 is reset.
            // 5-3      Unused
            // 2-0	    3 Most Significant bits of frequency
            // 1100 0011 is 0xC3, initialize, no consecutive, frequency = MSB + LSB = 011 0000 0000 = 0x300
            NR14_REG = 0xC3;

            delay(500);
        }
    }
    
}