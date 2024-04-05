#ifndef _JOYSTICK_CONTROL_H_
#define _JOYSTICK_CONTROL_H_


#include <stdio.h>
#include <pthread.h>

void Joystick_init(void);
void Joystick_join(void);

void Joystick_setOnTarget(void);

#endif