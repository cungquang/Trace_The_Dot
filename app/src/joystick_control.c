#include "../include/joystick_control.h"
#include "../include/accelerometer_control.h"
#include "../include/sharedData-Linux.h"
#include "../include/sound_control.h"
#include "../include/digits_control.h"

#define DELAY_MILLISECONDS 10
#define MULTIPLE_CLICK_BOUND 10
#define DEBOUNCE_LIMIT 10

//Manage operation
static int isTerminated = 0;

//Hit
static int status_curr = 0;
static long status_count = 0;
static int bounceBack_toZero = 0;
static long onTarget_count = 0;

//Thread
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

void Joystick_setOnTarget(void)
{
    onTarget_count += 1;
}

/*
#########################
#        PRIVATE        #
#########################
*/

static void * Joystick_observe()
{
    while(!isTerminated)
    {
        // User press fire
        if(joystickRight_preventDebounce(joystickDown_isPressed()))
        {
            // On target
            if(Accelerometer_aimAtTarget())
            {
                if(status_curr == 1 && status_count <= 1)
                {
                    Sound_setPlayHitOrMiss(1);
                    Joystick_setOnTarget();
                    Digits_setValueToDisplay(onTarget_count);
                }
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
            Digits_setTerminated();
        }

        sleepForMs(DELAY_MILLISECONDS);
    }

    return NULL;
}


static int joystickRight_preventDebounce(int downIsPressed)
{
    // user press down
    if(status_curr == 0 && downIsPressed == 1)
    {
        // printf("status----> %d    downispress----->%d    count-----> %d\n", status_curr, downIsPressed, status_count);
        status_count = downIsPressed;
        status_curr = 1;
        return 1;
    } 
    // Multiple press
    else if (status_curr == 1 && downIsPressed == 1)
    {
        status_count++;
        status_count = status_count > MULTIPLE_CLICK_BOUND? MULTIPLE_CLICK_BOUND : status_count;

        //Stop bounce back accumulate - must be continuous
        bounceBack_toZero = 0;
        return 1;
    }
    else if (status_curr == 1 && downIsPressed == 0)
    {
        // Actually back to 0
        if(bounceBack_toZero > DEBOUNCE_LIMIT)
        {
            status_count = 0;
            status_curr = 0;
            bounceBack_toZero = 0;
        }
        else{
            bounceBack_toZero++;
        }
    }
    else
    {
        status_count = 0;
        status_curr = 0;
        bounceBack_toZero = 0;
    }

    return 0;
}