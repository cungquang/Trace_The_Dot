#ifndef _DIGITS_CONTROL_H_
#define _DIGITS_CONTROL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../../hal/include/register_configure.h"

void Digits_init(void);
void Digits_join(void);
void Digits_cleanUp(void);
void Digits_setTerminated(void);
void Digits_setValueToDisplay(long displayValue);

#endif