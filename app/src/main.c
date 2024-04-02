#include "../include/neoPixelRGBW-Linux.h"
#include "../include/joystick-Linux.h"
#include "../include/i2cbus1_control.h"
#include <stdbool.h>


int main(void)
{
    // neoPixel_init();
    // I2cbus1Control_init();
    // I2cbus1Control_join();
    // neoPixel_cleanup();

    joystick_init();
    printf("Down is press: %d\n", joystickDown_isPressed());
    printf("Down is Count: %d\n", joystickDown_pressCount());
    printf("Right is press: %d\n", joystickRight_isPressed());
    printf("Right is Count: %d\n", joystickRight_pressCount());
    joystickDown_pressCount();

    joystick_cleanup();
}