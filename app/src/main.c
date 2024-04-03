#include "../include/i2cbus1_control.h"
#include "../include/sharedData-Linux.h"
#include <stdbool.h>


int main(void)
{
    neoPixel_init();
    I2cbus1Control_init();
    I2cbus1Control_join();
    neoPixel_cleanup();

    // neoPixel_init();
    // printf("Down is pressed: %d\n", joystickDown_isPressed());

    // printf("Right is pressed: %d\n", joystickRight_isPressed());
    // neoPixel_cleanup();
}