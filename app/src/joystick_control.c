#include "../include/joystick_control.h"
#include "../include/accelerometer_control.h"
#include "../include/sharedData-Linux.h"
#include "../include/sound_control.h"

static int isTerminated = 0;

static int joystickDown_count = 0;

static pthread_t sound_playTargetSoundThreadId;

// static pthread_mutex_t shared_section_mutex = PTHREAD_MUTEX_INITIALIZER;

//Iniatiate private
static void * Joystick_observe();
static int joystickRight_preventDebounce(int downIsPressed);

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
    pthread_join(sound_playTargetSoundThreadId, NULL);
}

//Write shutdown function here

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
        if(joystickRight_preventDebounce(joystickDown_isPressed()))
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
            isTerminated = 1;
            Pru_setTerminateFlag();
            Accelerometer_terminate();
            Sound_setTerminate();
        }
    }

    return NULL;
}


static int joystickRight_preventDebounce(int downIsPressed)
{
    // user press down
    if(downIsPressed)
    {
        // Not yet press for the first time
        if(joystickDown_count == 0)
        {
            joystickDown_count = 1;
            return 1;
        }
        // Have pressed before
        else
        {
            joystickDown_count = joystickDown_count + 1 > 2? 2 : joystickDown_count + 1;
        }
    }
    // user NOT press down
    else
    {
        joystickDown_count = 0;
    }

    return 0;
}