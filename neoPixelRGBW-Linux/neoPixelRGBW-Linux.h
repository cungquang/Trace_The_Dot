#ifndef _NEOPIXELRGBW_LINUX_H_
#define _NEOPIXELRGBW_LINUX_H_

#include <stdint.h>

void neoPixel_init(void);
void neoPixel_cleanup(void);

void setColor_ithPosition(uint32_t colorValue, int position);
void setColor_Background(uint32_t colorValue);

#endif