#include "./neoPixelRGBW-Linux.h"


// // Regular Color Value
// #define GREEN_COLOR     0x0f000000
// #define RED_COLOR       0x000f0000
// #define BLUE_COLOR      0x00000f00
// #define WHITE_COLOR     0x0000000f
// #define WHITE_COLOR_RGB 0x0f0f0f00
// #define YELLOW_COLOR    0x0f0f0000
// #define PURPLE_COLOR    0x000f0f00
// #define TEAL_COLOR      0x0f000f00

// // Bright Color Value
// #define GREEN_B_COLOR           0xff000000 // Green Bright
// #define RED_B_COLOR             0x00ff0000 // Red Bright
// #define BLUE_B_COLOR            0x0000ff00 // Blue Bright
// #define WHITE_B_COLOR           0xffffff00 // White
// #define GREEN_WHITE_B_COLOR     0xff0000ff // Green Bright w/ Bright White
// #define RED_WHITE_B_COLOR       0x00ff00ff // Red Bright w/ Bright White
// #define BLUE_WHITE_B_COLOR      0x0000ffff // Blue Bright w/ Bright White
// #define WHITE_BB_COLOR          0xffffffff // White w/ Bright White


int main(void)
{
    neoPixel_init();
    uint32_t background = 0x0000000f;
    uint32_t foreground = 0x000f0000;
    
    setColor_Background(background);
    setColor_ithPosition(foreground, 7);    
    neoPixel_cleanup();

}