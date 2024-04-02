#ifndef _NEOPIXELSHAREDDATASTRUCT_H_
#define _NEOPIXELSHAREDDATASTRUCT_H_

#include <stdint.h>

// WARNING:
// Fields in the struct must be aligned to match ARM's alignment
//    bool/char, uint8_t:   byte aligned
//    int/long,  uint32_t:  word (4 byte) aligned
//    double,    uint64_t:  dword (8 byte) aligned
// Add padding fields (char _p1) to pad out to alignment.

// My Shared Memory Structure
// ----------------------------------------------------------------
typedef struct {
    _Alignas(4) uint32_t position_1;
    _Alignas(4) uint32_t position_2;
    _Alignas(4) uint32_t position_3;
    _Alignas(4) uint32_t position_4;
    _Alignas(4) uint32_t position_5;
    _Alignas(4) uint32_t position_6;
    _Alignas(4) uint32_t position_7;
    _Alignas(4) uint32_t position_8;
    
    
} sharedMemStruct_t;

#endif
