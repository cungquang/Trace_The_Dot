#include "../include/joystick_control.h"
#include "../include/sharedData-Linux.h"

static int isTerminated = 0;

static pthread_mutex_t shared_pipe_mutex = PTHREAD_MUTEX_INITIALIZER;

void Joystick_init(void)
{

}


