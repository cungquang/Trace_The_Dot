#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "./neoPixelRGBW-Linux.h"
#include "../../pru-as4/neoPixelSharedDataStruct.h"

// Constant color
#define GREEN_COLOR     0x0f000000
#define RED_COLOR       0x000f0000
#define BLUE_COLOR      0x00000f00

#define GREEN_B_COLOR   0xff000000 // Green Bright
#define RED_B_COLOR     0x00ff0000 // Red Bright
#define BLUE_B_COLOR    0x0000ff00 // Blue Bright

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
volatile void* getPruMmapAddr(void);
void freePruMmapAddr(volatile void* pPruBase);

/*
#########################
#        PUBLIC         #
#########################
*/


void neoPixel_init(void)
{
    // Get access to shared memory for my uses
    pPruBase0 = getPruMmapAddr();
    pSharedPru0 = PRU0_MEM_FROM_BASE(pPruBase0);
}

void neoPixel_cleanup(void)
{
    freePruMmapAddr(pPruBase0);
}

/////////////////////////////// SETTER ///////////////////////////////

void setColor_background(uint32_t colorValue)
{
    //Set the color    
    pSharedPru0->position_1 = colorValue;
    pSharedPru0->position_2 = colorValue;
    pSharedPru0->position_3 = colorValue;
    pSharedPru0->position_4 = colorValue;
    pSharedPru0->position_5 = colorValue;
    pSharedPru0->position_6 = colorValue;
    pSharedPru0->position_7 = colorValue;
    pSharedPru0->position_8 = colorValue;
}

void setColor_ithPosition(uint32_t colorValue, int position)
{
    if(position == 1)
    {
        pSharedPru0->position_1 = colorValue;
    } 
    else if(position == 2)
    {
        pSharedPru0->position_2 = colorValue;
    }
    else if(position == 3)
    {
        pSharedPru0->position_3 = colorValue;
    }
    else if(position == 4)
    {
        pSharedPru0->position_4 = colorValue;
    }
    else if(position == 5) 
    {
        pSharedPru0->position_5 = colorValue;
    }
    else if(position == 6)
    {
        pSharedPru0->position_6 = colorValue;
    }
    else if(position == 7) 
    {
        pSharedPru0->position_7 = colorValue;
    }
    else if(position == 8)
    {
        pSharedPru0->position_8 = colorValue;
    }
}

/////////////////////////////// GETTER ///////////////////////////////

void getColor_background(float lean, uint32_t *background)
{
    //Lean to the left side - RED 
    if(lean > 0.45)
    {
        *background = 0x000f0000;
    }
    //Lean to the right side - GREEN
    else if(lean < -0.45) 
    {
        *background = 0x0f000000;
    }
    //At center - BLUE
    else
    {
        *background = 0x00000f00;
    }
    return;
}

void getColor_focusPoint(uint32_t *background, uint32_t *up_color, uint32_t *middle_color, uint32_t *down_color)
{
    // background is GREEN
    if(*background == GREEN_COLOR)
    {
        *up_color = GREEN_COLOR;
        *middle_color = GREEN_B_COLOR;
        *down_color = GREEN_COLOR;
    }
    
    // background is RED
    if(*background == RED_COLOR)
    {
        *up_color = RED_COLOR;
        *middle_color = RED_B_COLOR;
        *down_color = RED_COLOR;
    }

    // background is BLUE
    if(*background == BLUE_COLOR)
    {
        *up_color = BLUE_COLOR;
        *middle_color = BLUE_B_COLOR;
        *down_color = BLUE_COLOR;
    }    
    
    return;
}

void getPosition_focusPoint(float tilt, int *up, int *middle, int *down)
{
    /////////////// MOVING UP ///////////////
    if(tilt > 0.95)
    {
        *up = 10;
        *middle = 9;
        *down = 8;
        return;
    }
    //Moving up 0.8 < tilt <= 0.95
    if(tilt > 0.8 && tilt <= 0.95)
    {
        *up = 9;
        *middle = 8;
        *down = 7;
        return;
    }
    //Moving up 0.65 < tilt <= 0.8
    if(tilt > 0.65 && tilt <= 0.8)
    {
        *up = 8;
        *middle = 7;
        *down = 6;
        return;
    }

    //Moving up 0.5 < tilt <= 0.65
    if(tilt > 0.5 && tilt <= 0.65)
    {
        *up = 7;
        *middle = 6;
        *down = 5;
        return;
    }

    //Moving up 0.35 < tilt <= 0.5
    if(tilt > 0.35 && tilt <= 0.5)
    {
        *up = 6;
        *middle = 5;
        *down = 4;
        return;
    }

    /////////////// CENTER ///////////////
    //Within center
    if(tilt <= 0.35 && tilt >= -0.35)
    {
        *up = -1;
        *middle = -1;
        *down = -1;
        return;
    }

    /////////////// MOVING DOWN /////////////// 
    //Moving down -0.35 > tilt >= -0.5
    if(tilt < -0.35 && tilt >= -0.5)
    {
        *up = 4;
        *middle = 5;
        *down = 6;
        return;
    }

    //Moving down -0.5 > tilt >= -0.65
    if(tilt < -0.5 && tilt >= -0.65)
    {
        *up = 5;
        *middle = 6;
        *down = 7;
        return;
    }
    //Moving down -0.65 > tilt >= -0.8
    if(tilt < -0.65 && tilt >= -0.8)
    {
        *up = 6;
        *middle = 7;
        *down = 8;
        return;
    }
    //Moving down -0.8 > tilt >= -0.95
    if(tilt < -0.8 && tilt >= -0.95)
    {
        *up = 7;
        *middle = 8;
        *down = 9;
        return;
    }
    if(tilt < -0.95)
    {
        *up = 8;
        *middle = 9;
        *down = 10;
        return;
    }
}


/*
#########################
#       PRIVATE         #
#########################
*/


// Return the address of the PRU's base memory
volatile void* getPruMmapAddr(void)
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

void freePruMmapAddr(volatile void* pPruBase)
{
    if (munmap((void*) pPruBase, PRU_LEN)) {
        perror("PRU munmap failed");
        exit(EXIT_FAILURE);
    }
}
