#include "../include/pwm_configure.h"
#include "../../app/include/general_helper.h"

#define PWM_CONFIGURE_P922          "sudo config-pin p9_22 pwm"

#define PWM_PATH_TO_PERIOD          "/dev/bone/pwm/0/a/period"
#define PWM_PATH_TO_DUTYCYCLE       "/dev/bone/pwm/0/a/duty_cycle"

//Enable/disable the sound
#define PWM_SOUND_0_ENABLE          "echo 0 > /dev/bone/pwm/0/a/enable"
#define PWM_SOUND_1_ENABLE          "echo 1 > /dev/bone/pwm/0/a/enable"

//Reset duty cycle
#define PWM_RESET_DUTYCYCLE(PATH)   "echo 0 > " PATH

//Middle C - 261.6Hz
#define PWM_M_C_PERIOD(PATH)        "echo 3822256 > " PATH
#define PWM_M_C_DUTYCYCLE(PATH)     "echo 1911128 > " PATH

//High C - 541Hz
#define PWM_H_C_PERIOD(PATH)        "echo 1851851 > " PATH
#define PWM_H_C_DUTYCYCLE(PATH)     "echo 925925 > " PATH


//Initiate private function
void Pwm_setMiddleCNote(void);
void Pwm_setHighCNote(void);


/*
#########################
#        PUBLIC         #
#########################
*/


void Pwm_init(void)
{
    runCommand(PWM_CONFIGURE_P922);
}

void Pwm_playMiddleCNote(int millisecond)
{
    // if enable -> Clear current sound
    //runCommand(PWM_SOUND_0_ENABLE);

    // Set frequency
    Pwm_setMiddleCNote();

    // Play the sound
    runCommand(PWM_SOUND_1_ENABLE);
    sleepForMs(millisecond);
    runCommand(PWM_SOUND_0_ENABLE);
    runCommand(PWM_SOUND_1_ENABLE);
    sleepForMs(millisecond);

    // End the sound
    runCommand(PWM_SOUND_0_ENABLE);
}


void Pwm_playHighCNote(int millisecond)
{
    // if enable -> Clear current sound
    //runCommand(PWM_SOUND_0_ENABLE);

    // Set frequency
    Pwm_setHighCNote();

    // Play the sound
    runCommand(PWM_SOUND_1_ENABLE);
    sleepForMs(millisecond);
    runCommand(PWM_SOUND_0_ENABLE);
    runCommand(PWM_SOUND_1_ENABLE);
    sleepForMs(millisecond);

    // End the sound
    runCommand(PWM_SOUND_0_ENABLE);
}


/*
#########################
#        PRIVATE        #
#########################
*/

void Pwm_setMiddleCNote(void)
{
    runCommand(PWM_RESET_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
    runCommand(PWM_M_C_PERIOD(PWM_PATH_TO_PERIOD));
    runCommand(PWM_M_C_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
}


void Pwm_setHighCNote(void)
{
    runCommand(PWM_RESET_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
    runCommand(PWM_H_C_PERIOD(PWM_PATH_TO_PERIOD));
    runCommand(PWM_H_C_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
}
