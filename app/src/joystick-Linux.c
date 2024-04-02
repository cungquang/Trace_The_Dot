#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "../include/joystick-Linux.h"
#include "../../pru-as4/neoPixel/neoPixelSharedDataStruct.h"
#include "../include/general_helper.h"

#define CONFIGURE_PIN_815 "config-pin p8_15 pruin"
#define CONFIGURE_PIN_816 "config-pin p8_16 pruin"

// General PRU Memomry Sharing Routine
// ----------------------------------------------------------------
#define PRU_ADDR            0x4A300000   // Start of PRU memory Page 184 am335x TRM
#define PRU_LEN             0x80000      // Length of PRU memory
#define PRU0_DRAM           0x00000      // Offset to DRAM
#define PRU1_DRAM           0x02000
#define PRU_SHAREDMEM       0x10000      // Offset to shared memory
#define PRU_MEM_RESERVED    0x200        // Amount used by stack and heap

// Convert base address to each memory section
#define PRU0_MEM_FROM_BASE(base) ((volatile sharedMemStruct_t *)((uintptr_t)(base) + PRU0_DRAM + PRU_MEM_RESERVED))
#define PRU1_MEM_FROM_BASE(base) ((volatile sharedMemStruct_t *)((uintptr_t)(base) + PRU1_DRAM + PRU_MEM_RESERVED))
#define PRUSHARED_MEM_FROM_BASE(base) ( (base) + PRU_SHAREDMEM)

//Pointer
volatile void *pPruBase0;
volatile sharedMemStruct_t *pSharedPru0;

//Initiate private function
volatile void* joystick_getPruMmapAddr(void);
void joystick_freePruMmapAddr(volatile void* pPruBase);


/*
#########################
#        PUBLIC         #
#########################
*/


void joystick_init(void)
{
    runCommand(CONFIGURE_PIN_815);
    runCommand(CONFIGURE_PIN_816);
    
    // Get access to shared memory for my uses
    pPruBase0 = joystick_getPruMmapAddr();
    pSharedPru0 = PRU0_MEM_FROM_BASE(pPruBase0);
}

void joystick_cleanup(void)
{
    joystick_freePruMmapAddr(pPruBase0);
}

bool joystickDown_isPressed(void)
{
    return pSharedPru0->joystickDown_isPressed;
}

bool joystickRight_isPressed(void)
{
    return pSharedPru0->joystickRight_isPressed;
}

/*
#########################
#       PRIVATE         #
#########################
*/

// Return the address of the PRU's base memory
volatile void* joystick_getPruMmapAddr(void)
{
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        perror("ERROR: could not open /dev/mem");
        exit(EXIT_FAILURE);
    }

    // Points to start of PRU memory.
    volatile void* pPruBase = mmap(0, PRU_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, PRU_ADDR);
    if (pPruBase == MAP_FAILED) {
        perror("ERROR: could not map memory");
        exit(EXIT_FAILURE);
    }
    close(fd);

    return pPruBase;
}

void joystick_freePruMmapAddr(volatile void* pPruBase)
{
    if (munmap((void*) pPruBase, PRU_LEN)) {
        perror("PRU munmap failed");
        exit(EXIT_FAILURE);
    }
}