#ifndef _SHAREDDATA_LINUX_H_
#define _SHAREDDATA_LINUX_H_

#include <stdint.h>
#include <stdbool.h>

void SharedData_init(void);
void SharedData_cleanup(void);

void Pru_setTerminateFlag(void);

void setColor_background(uint32_t colorValue);
void setColor_ithPosition(uint32_t colorValue, int position);

void getColor_background(float lean, uint32_t *background, float centerUpper, float centerLower);
void getColor_focusPoint(uint32_t *background, uint32_t *up_color, uint32_t *middle_color, uint32_t *down_color);
void getPosition_focusPoint(float tilt, int *up, int *middle, int *down, float centerUpper, float centerLower);

// Joystick
bool joystickDown_isPressed(void);
bool joystickRight_isPressed(void);

#endif