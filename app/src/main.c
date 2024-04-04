#include "../include/accelerometer_control.h"
#include "../include/sharedData-Linux.h"
#include "../include/joystick_control.h"
#include "../include/sound_control.h"
#include "../../hal/include/register_configure.h"
#include <stdbool.h>


void operation(void)
{
    //Initiate SharedData
    SharedData_init();

    // Main operation
    Joystick_init();
    Sound_init();
    Accelerometer_init();

    //Join
    Accelerometer_join();
    Sound_join();
    Joystick_join();

    // Cleanup share data
    SharedData_cleanup();
}

int main(void)
{
    I2cbus1_init();
    I2cbus1_enableRightDigit();
    I2cbus1_enableLeftDigit();
    while(true)
    {
        I2cbus1Write_No8();
        sleepForMs(100);
        I2cbus1Write_No9();
        sleepForMs(100);
    }
    //operation();
}