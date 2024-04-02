#include "../include/neoPixelRGBW-Linux.h"
#include "../include/joystick-Linux.h"
#include "../include/i2cbus1_control.h"
#include <stdbool.h>

#define CONFIGURE_PIN_815 "config-pin p8_15 pruin"
#define CONFIGURE_PIN_816 "config-pin p8_16 pruin"

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