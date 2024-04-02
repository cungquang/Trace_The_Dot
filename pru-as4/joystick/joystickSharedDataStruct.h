#ifndef _JOYSTICKSHAREDDATASTRUCT_H_H
#define _JOYSTICKSHAREDDATASTRUCT_H_H

#include <stdint.h>
#include <stdbool.h>

// WARNING:
// Fields in the struct must be aligned to match ARM's alignment
//    bool/char, uint8_t:   byte aligned
//    int/long,  uint32_t:  word (4 byte) aligned
//    double,    uint64_t:  dword (8 byte) aligned
// Add padding fields (char _p1) to pad out to alignment.

// My Shared Memory Structure
// ----------------------------------------------------------------
typedef struct {
    bool joystickDown_isPressed;
    bool joystickRight_isPressed;
    _Alignas(4) uint32_t joystickDown_count;
    _Alignas(4) uint32_t joystickRight_count;
    
} jsSharedMemStruct_t;

#endif
