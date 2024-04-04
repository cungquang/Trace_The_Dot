#include "../include/general_helper.h"
#include "../include/sound_control.h"
#include "../../hal/include/pwm_configure.h"

//Control operation
static int isTerminate = 0;

//Status to trigger play sound
static int playHitOrMiss = 0;

//Threads
static pthread_t sound_playTargetSoundThreadId;

//Mutex
static pthread_mutex_t shared_section_mutex = PTHREAD_MUTEX_INITIALIZER;


//Initiate private function
static void * Sound_playTargetSound();
static void Sound_playHitTarget(void);
static void Sound_playMissTarget(void);


/*
#########################
#        PUBLIC         #
#########################
*/

void Sound_init(void)
{
    //Configure the pin
    Pwm_init();

    //Create thread
    pthread_create(&sound_playTargetSoundThreadId, NULL, Sound_playTargetSound, NULL);
}

void Sound_join(void)
{
    pthread_join(&sound_playTargetSoundThreadId, NULL);
}

void Sound_cleanup(void)
{
    playHitOrMiss = 0;
}

void Sound_setTerminate(void)
{
    isTerminate = 1;
}

void Sound_setPlayHitOrMiss(int hitOrMiss)
{
    pthread_mutex_lock(&shared_section_mutex);
    playHitOrMiss = hitOrMiss;
    pthread_mutex_unlock(&shared_section_mutex);
}

/*
#########################
#        PRIVATE        #
#########################
*/

static void * Sound_playTargetSound()
{
    while(!isTerminate)
    {
        pthread_mutex_lock(&shared_section_mutex);
        if(playHitOrMiss == 1)
        {
            Sound_playHitTarget();
            playHitOrMiss = 0;
        }
        else if(playHitOrMiss == 2)
        {
            Sound_playMissTarget();
            playHitOrMiss = 0;
        }
        pthread_mutex_unlock(&shared_section_mutex);

        // Delay before recheck
        sleepForMs(10);
    }

    return NULL;
}

static void Sound_playHitTarget(void)
{
    Pwm_playHighFNote(200);
    Pwm_playHighENote(30);
    Pwm_playHighENote(50);
    Pwm_playHighENote(80);
    Pwm_playHighENote(100);
}

static void Sound_playMissTarget(void)
{
    Pwm_playMiddleCNote(60);
    Pwm_playMiddleCNote(60);
    Pwm_playLowDNote(150);
}