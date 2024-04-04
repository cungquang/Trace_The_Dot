#ifndef _SOUND_CONTROL_H_
#define _SOUND_CONTROL_H_

#include <stdio.h>
#include <pthread.h>

void Sound_init(void);
void Sound_join(void);
void Sound_setTerminate(void);

void Sound_setPlayHitTarget(void);
void Sound_setPlayMissTarget(void);

#endif