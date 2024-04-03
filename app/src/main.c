#include "../include/accelerometer_control.h"
#include "../include/sharedData-Linux.h"
#include <stdbool.h>


int main(void)
{
    neoPixel_init();
    Accelerometer_init();
    Accelerometer_join();
    neoPixel_cleanup();

    // neoPixel_init();
    // printf("Down is pressed: %d\n", joystickDown_isPressed());

    // printf("Right is pressed: %d\n", joystickRight_isPressed());
    // neoPixel_cleanup();
}