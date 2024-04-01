#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "./neoPixelRGBW-Linux.h"
#include "./neoPixelSharedDataStruct.h"


// // Regular Color Value
// #define GREEN_COLOR     0x0f000000
// #define RED_COLOR       0x000f0000
// #define BLUE_COLOR      0x00000f00
// #define WHITE_COLOR     0x0000000f
// #define WHITE_COLOR_RGB 0x0f0f0f00
// #define YELLOW_COLOR    0x0f0f0000
// #define PURPLE_COLOR    0x000f0f00
// #define TEAL_COLOR      0x0f000f00

// // Bright Color Value
// #define GREEN_B_COLOR           0xff000000 // Green Bright
// #define RED_B_COLOR             0x00ff0000 // Red Bright
// #define BLUE_B_COLOR            0x0000ff00 // Blue Bright
// #define WHITE_B_COLOR           0xffffff00 // White
// #define GREEN_WHITE_B_COLOR     0xff0000ff // Green Bright w/ Bright White
// #define RED_WHITE_B_COLOR       0x00ff00ff // Red Bright w/ Bright White
// #define BLUE_WHITE_B_COLOR      0x0000ffff // Blue Bright w/ Bright White
// #define WHITE_BB_COLOR          0xffffffff // White w/ Bright White



// General PRU Memomry Sharing Routine
// ----------------------------------------------------------------
#define PRU_ADDR      0x4A300000   // Start of PRU memory Page 184 am335x TRM
#define PRU_LEN       0x80000      // Length of PRU memory
#define PRU0_DRAM     0x00000      // Offset to DRAM
#define PRU1_DRAM     0x02000
#define PRU_SHAREDMEM 0x10000      // Offset to shared memory
#define PRU_MEM_RESERVED 0x200     // Amount used by stack and heap

// Convert base address to each memory section
#define PRU0_MEM_FROM_BASE(base) ( (base) + PRU0_DRAM + PRU_MEM_RESERVED)
#define PRU1_MEM_FROM_BASE(base) ( (base) + PRU1_DRAM + PRU_MEM_RESERVED)
#define PRUSHARED_MEM_FROM_BASE(base) ( (base) + PRU_SHAREDMEM)

//
volatile void *pPruBase0;
volatile sharedMemStruct_t *pSharedPru0;

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

void setColor_Background(uint32_t colorValue)
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
    else
    {
        printf("ERROR: Invalid NEO position\n");
    }
}

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