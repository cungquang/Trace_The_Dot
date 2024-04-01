#include "./neoPixelRGBW-Linux.h"
#include "../include/i2cbus1_control.h"
#include "../include/general_helper.h"
#include "../../hal/include/i2c_configure.h"

#define P8_11_STATE_PATH "/sys/devices/platform/ocp/ocp:P8_11_pinmux/state"
#define CONFIGURE_PIN_811 "config-pin P8.11 pruout > /dev/null"

int main(void)
{
    neoPixel_init();
    I2cbus1Control_init();
    I2cbus1Control_join();
    neoPixel_cleanup();
}