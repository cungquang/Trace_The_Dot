#include "../../hal/include/pwm_configure.h"

static int hit_count;

//Initiate private function
static void Sound_init(void);
static void Sound_playHitTarget(void);
static void Sound_playMissTarget(void);


static void Sound_init(void)
{
    //Configure the pin
    Pwm_init();
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