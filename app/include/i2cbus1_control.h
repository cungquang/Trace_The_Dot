#ifndef _I2CBUS1_CONTROL_H_
#define _I2CBUS1_CONTROL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>
#include "../../hal/include/register_configure.h"

void I2cbus1Control_init(void);
void I2cbus1Control_join(void);
void I2cbus1Control_cleanup(void);
void I2cbusControl_terminate(void);

#endif