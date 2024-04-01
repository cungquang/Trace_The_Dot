#include "../include/i2cbus1_control.h"

#define TRIGGER_BIT 0x27
#define BUFFER_SIZE 2
#define RESOLUTION_8BITS_SHIFT 16000
#define SELECT_SCALE 2
#define XY_FREQUENCY 100

//Operation
static int isTerminate = 0;

//Focus point
static int focus_up;
static int focus_middle;
static int focus_down;

//Raw data G-force
static unsigned char xen_L_H[BUFFER_SIZE];
static unsigned char yen_L_H[BUFFER_SIZE];

//Converted G-force value
static float xenH_curr;
static float yenH_curr;

//Threads
static pthread_t i2cbus1XYenH_id;

//Mutex
static pthread_mutex_t shared_pipe_mutex = PTHREAD_MUTEX_INITIALIZER;

//Initiate private function
static void* I2cbus1readXYenH_thread();
static int16_t I2cbus1_getRawData(int8_t rawL, int8_t rawH);
static float I2cbus1_convertToGForce(int16_t rawData);


/*
#########################
#        PUBLIC         #
#########################
*/

void I2cbus1Control_init(void)
{
    //Configure bus & register
    I2cbus1_init();
    I2cbus1Write_Reg1(TRIGGER_BIT);

    if(I2cbus1Read_Reg1() != TRIGGER_BIT) 
    {
        printf("ERROR: fail to switch power mode and enable sensor.\n");
        exit(EXIT_FAILURE);
    }

    pthread_create(&i2cbus1XYenH_id, NULL, I2cbus1readXYenH_thread, NULL);
}


void I2cbus1Control_join(void)
{
    pthread_join(i2cbus1XYenH_id, NULL);
}


void I2cbus1Control_cleanup(void)
{
    xenH_curr = 0;
    yenH_curr = 0;

    memset(xen_L_H, 0, sizeof(xen_L_H));
    memset(yen_L_H, 0, sizeof(yen_L_H));
}

void I2cbusControl_terminate(void)
{
    isTerminate = 1;
}


/*
#########################
#       PRIVATE         #
#########################
*/

// X_axis move side by side 
static void* I2cbus1readXYenH_thread()
{  
    while(!isTerminate)
    {
        //Convert raw to G force value

        //X value: LEFT - RIGHT
        xen_L_H[0] = I2cbus1Read_OutXL();
        xen_L_H[1] = I2cbus1Read_OutXH();
        xenH_curr = I2cbus1_convertToGForce(I2cbus1_getRawData(xen_L_H[0], xen_L_H[1]));

        //Y value: UP - DOWN
        yen_L_H[0] = I2cbus1Read_OutYL();
        yen_L_H[1] = I2cbus1Read_OutYH();
        yenH_curr = I2cbus1_convertToGForce(I2cbus1_getRawData(yen_L_H[0], yen_L_H[1]));
        
        pthread_mutex_lock(&shared_pipe_mutex);
        printf("Tilt value: %.2f\n", xenH_curr);
        pthread_mutex_unlock(&shared_pipe_mutex);
        
        sleepForMs(XY_FREQUENCY);
    }

    return NULL;
}

static int16_t I2cbus1_getRawData(int8_t rawL, int8_t rawH)
{
    return (rawH << 8) | (rawL);
}

static float I2cbus1_convertToGForce(int16_t rawData)
{
    return (float)rawData/RESOLUTION_8BITS_SHIFT;
}