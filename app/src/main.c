#include "./neoPixelRGBW-Linux.h"
#include "../include/i2cbus1_control.h"
#include "../include/general_helper.h"

#define P8_11_STATE_PATH "/sys/devices/platform/ocp/ocp:P8_11_pinmux/state"
#define CONFIGURE_PIN_811 "config-pin P8.11 pruout > /dev/null"

int main(void)
{
    runCommand(CONFIGURE_PIN_811);
    print("%d\n", isI2cConfigure_p811());
    // neoPixel_init();
    // I2cbus1Control_init();
    // I2cbus1Control_join();
    // neoPixel_cleanup();
}