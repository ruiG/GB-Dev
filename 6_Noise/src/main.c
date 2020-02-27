#include <gb/gb.h>

void main(){

    NR52_REG = 0x80; // 1000 0000 - turn on the sound
    NR50_REG = 0x77; // 0111 0111‬ - left and right channel volume to max
    NR51_REG = 0xFF; // 1111 1111 - select which channels - all of them for both channels

    while (1)
    {
        UBYTE joypad_state = joypad();

        if(joypad_state) {

            // channel 4 register 1, Noise Length
            // 0001 111 is 0x1F, maximum length
            NR41_REG = 0x1F;

            // channel 4 register 2, Volume envelope
            // 7-4      initial channel volume
            // 3        volume direction (0 down, 1 up)
            // 2-0      volume envelope length (0-7)
            // 1111 0001 is 0xF1, Max Volume, fade down, 1 sweep
            NR42_REG = 0xF1;

            // channel 4 register 3
            // 7-4      Shift clock frequency (s)
            // 3        Counter step (0=15 bits, 1=7bits)
            // 2-0      Dividing ration of frequencies (r)
            // The amplitude is randomly switched between high and low at the given frequency. 
            // A higher frequency will make the noise to appear 'softer'. 
            // When Bit 3 is set, the output will become more regular, and some frequencies will sound more like Tone than Noise.
            // 0011 0000 is 0x30, shift clock frequency 3, step 0, dividing ratio 0
            NR43_REG = 0x30;

            // 7   - Initial (1=Restart Sound)
            // 6   - Controls if last forever or stops when NR41 ends
            // (1=Stop output when length in NR41 expires)
            // 5-0	Unused
            // 1100 0000, start sound, not continuous
            NR44_REG = 0xC0;  

            delay(500);
        }
    }
    
}
