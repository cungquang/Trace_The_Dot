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

//Low D - 73.42Hz
#define PWM_L_D_PERIOD(PATH)        "echo 13620267 > " PATH
#define PWM_L_D_DUTYCYCLE(PATH)     "echo 6810134 > " PATH

//Middle C - 261.6Hz
#define PWM_M_C_PERIOD(PATH)        "echo 3822256 > " PATH
#define PWM_M_C_DUTYCYCLE(PATH)     "echo 1911128 > " PATH

//High C - 2093Hz
#define PWM_H_C_PERIOD(PATH)        "echo 477783 > " PATH
#define PWM_H_C_DUTYCYCLE(PATH)     "echo 238892 > " PATH

//High E - 2673.02Hz
#define PWM_H_E_PERIOD(PATH)        "echo 379216 > " PATH
#define PWM_H_E_DUTYCYCLE(PATH)     "echo 189607 > " PATH

//High F - 3322.44Hz
#define PWM_H_F_PERIOD(PATH)        "echo 300984 > " PATH
#define PWM_H_F_DUTYCYCLE(PATH)     "echo 250492 > " PATH

//High A - 3520Hz
#define PWM_H_A_PERIOD(PATH)        "echo 284091 > " PATH
#define PWM_H_A_DUTYCYCLE(PATH)     "echo 142046 > " PATH

//High B - 7902Hz
#define PWM_H_B_PERIOD(PATH)        "echo 253100 > " PATH
#define PWM_H_B_DUTYCYCLE(PATH)     "echo 226550 > " PATH


//Initiate private function
void Pwm_triggerSound1Times(int milliseconds);
void Pwm_setLowDNote(void);
void Pwm_setMiddleCNote(void);
void Pwm_setHighCNote(void);
void Pwm_setHighANote(void);
void Pwm_setHighBNote(void);
void Pwm_setHighENote(void);
void Pwm_setHighFNote(void);

/*
#########################
#        PUBLIC         #
#########################
*/


void Pwm_init(void)
{
    runCommand(PWM_CONFIGURE_P922);
}

//////////////////////// Low Notes ////////////////////////

void Pwm_playLowDNote(int millisecond)
{
    //Set frequency
    Pwm_setLowDNote();
    Pwm_triggerSound1Times(millisecond);
}

//////////////////////// Middle Notes ////////////////////////

// Play Middle C note
void Pwm_playMiddleCNote(int millisecond)
{
    // Set frequency
    Pwm_setMiddleCNote();
    Pwm_triggerSound1Times(millisecond);
}

//////////////////////// High Notes ////////////////////////

// Play High A note
void Pwm_playHighANote(int millisecond)
{
    // Set frequency
    Pwm_setHighANote();
    Pwm_triggerSound1Times(millisecond);
}

// Play High B note
void Pwm_playHighBNote(int millisecond)
{
    // Set frequency
    Pwm_setHighBNote();
    Pwm_triggerSound1Times(millisecond);
}

// Play High C note
void Pwm_playHighCNote(int millisecond)
{
    // Set frequency
    Pwm_setHighCNote();
    Pwm_triggerSound1Times(millisecond);
}

// Play High E note
void Pwm_playHighFNote(int millisecond)
{
    // Set frequency
    Pwm_setHighFNote();
    Pwm_triggerSound1Times(millisecond);
}

// Play High E note
void Pwm_playHighENote(int millisecond)
{
    // Set frequency
    Pwm_setHighENote();
    Pwm_triggerSound1Times(millisecond);
}

/*
#########################
#        PRIVATE        #
#########################
*/

void Pwm_triggerSound1Times(int milliseconds)
{
    runCommand(PWM_SOUND_0_ENABLE);

    // Play the sound
    runCommand(PWM_SOUND_1_ENABLE);
    sleepForMs(milliseconds);

    // End the sound
    runCommand(PWM_SOUND_0_ENABLE);
}

//////////////////////// Low Notes ////////////////////////

void Pwm_setLowDNote(void)
{
    runCommand(PWM_RESET_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
    runCommand(PWM_L_D_PERIOD(PWM_PATH_TO_PERIOD));
    runCommand(PWM_L_D_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
}


//////////////////////// Middle Notes ////////////////////////

void Pwm_setMiddleCNote(void)
{
    runCommand(PWM_RESET_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
    runCommand(PWM_M_C_PERIOD(PWM_PATH_TO_PERIOD));
    runCommand(PWM_M_C_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
}

//////////////////////// High Notes ////////////////////////

void Pwm_setHighANote(void)
{
    runCommand(PWM_RESET_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
    runCommand(PWM_H_A_PERIOD(PWM_PATH_TO_PERIOD));
    runCommand(PWM_H_A_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));  
}

void Pwm_setHighBNote(void)
{
    runCommand(PWM_RESET_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
    runCommand(PWM_H_B_PERIOD(PWM_PATH_TO_PERIOD));
    runCommand(PWM_H_B_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));  
}

void Pwm_setHighCNote(void)
{
    runCommand(PWM_RESET_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
    runCommand(PWM_H_C_PERIOD(PWM_PATH_TO_PERIOD));
    runCommand(PWM_H_C_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
}

void Pwm_setHighENote(void)
{
    runCommand(PWM_RESET_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
    runCommand(PWM_H_E_PERIOD(PWM_PATH_TO_PERIOD));
    runCommand(PWM_H_E_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));   
}

void Pwm_setHighFNote(void)
{
    runCommand(PWM_RESET_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));
    runCommand(PWM_H_F_PERIOD(PWM_PATH_TO_PERIOD));
    runCommand(PWM_H_F_DUTYCYCLE(PWM_PATH_TO_DUTYCYCLE));   
}
