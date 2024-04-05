#include "../include/digitSegment_control.h"
#include "../../hal/include/register_configure.h"
#include "../include/sharedData-Linux.h"

static int isTerminated = 0;

void digitSegment_test(void)
{
    while(!isTerminate)
    {
        //Turn off both digit
        while()
        //Write left 
        I2cbus1Write_No1();
        
        sleepForMs(250);

        //Write right`
        I2cbus1Write_No9();
        // I2cbus1_enableRightDigit();
        sleepForMs(150);

    }
}

