#ifndef _ACCELEROMETER_CONTROL_H_
#define _ACCELEROMETER_CONTROL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>
#include "../../hal/include/register_configure.h"

void Accelerometer_init(void);
void Accelerometer_join(void);
void Accelerometer_cleanup(void);
void Accelerometer_terminate(void);

#endif