#ifndef _NEOPIXELRGBW_LINUX_H_
#define _NEOPIXELRGBW_LINUX_H_

#include <stdint.h>

void neoPixel_init(void);
void neoPixel_cleanup(void);

void setColor_background(uint32_t colorValue);
void setColor_ithPosition(uint32_t colorValue, int position);

void getColor_background(float lean, uint32_t *background);
void getColor_focusPoint(uint32_t *background, uint32_t *up_color, uint32_t *middle_color, uint32_t *down_color);
void getPosition_focusPoint(float tilt, int *up, int *middle, int *down);


#endif