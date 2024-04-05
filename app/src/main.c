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
    
    while(1)
    {
        //Turn off both digit
        // I2cbus1_disableRightDigit();
        // I2cbus1_disableLeftDigit();    

        //Write left 
        I2cbus1Write_No1();
        // I2cbus1_enableLeftDigit();
        sleepForMs(250);

        //Write right`
        I2cbus1Write_No9();
        // I2cbus1_enableRightDigit();
        sleepForMs(150);

    }

    //operation();
}