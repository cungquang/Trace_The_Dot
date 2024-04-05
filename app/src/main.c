#include "../include/accelerometer_control.h"
#include "../include/sharedData-Linux.h"
#include "../include/joystick_control.h"
#include "../include/sound_control.h"
#include "../../hal/include/register_configure.h"
#include "../include/digits_control.h"


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
    Digits_setValueToDisplay(29);
    
    Digits_init();
    Digits_join();
    

    //operation();
}