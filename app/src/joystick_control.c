#include "../include/joystick_control.h"
#include "../include/accelerometer_control.h"
#include "../include/sharedData-Linux.h"
#include "../include/sound_control.h"

static int isTerminated = 0;

static pthread_t sound_playTargetSoundThreadId;

static pthread_mutex_t shared_section_mutex = PTHREAD_MUTEX_INITIALIZER;

//Iniatiate private
static void * Joystick_observe();

/*
#########################
#        PUBLIC         #
#########################
*/

void Joystick_init(void)
{
    //Create thread
    pthread_create(&sound_playTargetSoundThreadId, NULL, Joystick_observe, NULL);
}

void Joystick_join(void)
{
    pthread_join(Joystick_observe, NULL);
}

/*
#########################
#        PRIVATE        #
#########################
*/

static void * Joystick_observe()
{
    while(isTerminated)
    {
        // Joystick Down is press -> shoot
        if(joystickDown_isPressed())
        {
            // On target
            if(Accelerometer_aimAtTarget())
            {
                Sound_setPlayHitOrMiss(1);
            }
            // Miss target
            else
            {
                Sound_setPlayHitOrMiss(2);
            }
        }
        
        // Joystick Right is press -> shutdown
        if(joystickRight_isPressed())
        {
            Accelerometer_terminate();
            Sound_setTerminate();
        }
    }

    return NULL;
}
