#include "./neoPixelRGBW-Linux.h"
#include "../include/i2cbus1_control.h"

int main(void)
{
    neoPixel_init();
    I2cbus1Control_init();
    I2cbus1Control_join();
    neoPixel_cleanup();
}