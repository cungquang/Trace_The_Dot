/*
    NeoPixel RGBW demo program for 8 LED unit such as:
        https://www.adafruit.com/product/2868
    NOTE: This is RGBW, not RGB!

    Install process
    - Put the NeoPixel into a breadboard
    - Connect the NeoPixel with 3 wires:
        - Connect NeoPixel "GND" and "DIN" (data in) to the 3-pin "LEDS" header on Zen
            Zen Cape's LEDS header:
                Pin 1: DIN (Data): left most pin; beside USB-micro connection, connects to P8.11
                Pin 2: GND (Ground): middle pin
                Pin 3: Unused (it's "5V external power", which is not powered normally on the BBG)
        - Connect NeoPixel "5VDC" to P9.7 or P9.8
            Suggest using the header-extender to make it easier to make a good connection.
        - OK to wire directly to BBG: no level shifter required.
    - Software Setup
        - On Host
            make      # on parent folder to copy to NFS
        - On Target: 
            config-pin P8.11 pruout
            make
            make install_PRU0
    - All lights should light up on the LED strip

    Based on code from the PRU Cookbook by Mark A. Yoder:
        https://beagleboard.org/static/prucookbook/#_setting_neopixels_to_different_colors
*/

#include <stdint.h>
#include <pru_cfg.h>
#include <stdbool.h>
#include "resource_table_empty.h"
#include "./sharedDataStruct.h"

#define STR_LEN         8       // # LEDs in our string
#define oneCyclesOn     700/5   // Stay on 700ns
#define oneCyclesOff    800/5
#define zeroCyclesOn    350/5
#define zeroCyclesOff   600/5
#define resetCycles     60000/5 // Must be at least 50u, use 60u

#define SPEED 200000000/5    // Time to wait between updates

volatile register uint32_t __R30;
volatile register uint32_t __R31;

// P8_12 for input (on R30) - 14-Seg Display 
#define DIGIT_ON_OFF_MASK (1 << 14)

// P8_11 for output (on R30), PRU0
#define DATA_PIN 15                             // Bit number to output one

// P8_15 for input (on R31), PRU0 (button right)
#define JOYSTICK_RIGHT_MASK (1 << 15)

// P8_16 for input (on R31), PRU0 (button down)
#define JOYSTICK_DOWN_MASK (1 << 14)

//Shared memory
#define THIS_PRU_DRAM1       0x02000         // Address of DRAM - PRU0
#define THIS_PRU_DRAM       0x00000         // Address of DRAM - PRU0
#define OFFSET              0x200           // Skip 0x100 for Stack, 0x100 for Heap (from makefile)
#define THIS_PRU_DRAM_USABLE (THIS_PRU_DRAM + OFFSET)

int isTerminated = 0;

volatile sharedMemStruct_t *pSharedMemStruct = (volatile void *)THIS_PRU_DRAM_USABLE;

//initiate private function
void displayLED(uint32_t * color);
void shutDown(uint32_t * color);


void main(void)
{
    //Start the program
    pSharedMemStruct->terminate_flag = isTerminated;

    // Clear SYSCFG[STANDBY_INIT] to enable OCP master port
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

    //Init color array
    uint32_t color[STR_LEN];

    while(!isTerminated) 
    {
        isTerminated = pSharedMemStruct->terminate_flag;

        // Down is pressed
        pSharedMemStruct->joystickDown_isPressed = (__R31 & JOYSTICK_DOWN_MASK) == 0;
        pSharedMemStruct->joystickRight_isPressed = (__R31 & JOYSTICK_RIGHT_MASK) == 0;

        // COLOURS
        // - 1st element in array is 1st (bottom) on LED strip; last element is last on strip (top)
        // - Bits: {Green/8 bits} {Red/8 bits} {Blue/8 bits} {White/8 bits}
        color[0] = pSharedMemStruct->position_1;
        color[1] = pSharedMemStruct->position_2;
        color[2] = pSharedMemStruct->position_3;
        color[3] = pSharedMemStruct->position_4;
        color[4] = pSharedMemStruct->position_5;
        color[5] = pSharedMemStruct->position_6;
        color[6] = pSharedMemStruct->position_7;
        color[7] = pSharedMemStruct->position_8;

        if(pSharedMemStruct->terminate_flag)
        {
            shutDown(color);
        }

        //Send to LED to display
        displayLED(color);      
    }
}

void shutDown(uint32_t *color)
{
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    color[3] = 0;
    color[4] = 0;
    color[5] = 0;
    color[6] = 0;
    color[7] = 0;
}

void displayLED(uint32_t * color)
{
    __delay_cycles(resetCycles);

    // Output the string
    for(int j = 0; j < STR_LEN; j++) {
        for(int i = 31; i >= 0; i--) {
            if(color[j] & ((uint32_t)0x1 << i)) {
                __R30 |= 0x1<<DATA_PIN;      // Set the GPIO pin to 1
                __delay_cycles(oneCyclesOn-1);
                __R30 &= ~(0x1<<DATA_PIN);   // Clear the GPIO pin
                __delay_cycles(oneCyclesOff-2);
            } else {
                __R30 |= 0x1<<DATA_PIN;      // Set the GPIO pin to 1
                __delay_cycles(zeroCyclesOn-1);
                __R30 &= ~(0x1<<DATA_PIN);   // Clear the GPIO pin
                __delay_cycles(zeroCyclesOff-2);
            }
        }
    }

    // Send Reset
    __R30 &= ~(0x1<<DATA_PIN);   // Clear the GPIO pin
    __delay_cycles(resetCycles);

    // Wait between update
    __delay_cycles(SPEED);
}

