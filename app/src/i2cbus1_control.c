#include "../include/i2cbus1_control.h"

#define TRIGGER_BIT 0x27
#define BUFFER_SIZE 2
#define RESOLUTION_8BITS_SHIFT 16000
#define SELECT_SCALE 2
#define X_FREQUENCY 100
#define Y_FREQUENCY 125
#define Z_FREQUENCY 100

//Operation
static int isTerminate = 0;

unsigned char xen_L_H[BUFFER_SIZE];
unsigned char yen_L_H[BUFFER_SIZE];
unsigned char zen_L_H[BUFFER_SIZE];

static float xenH_curr;
static float yenH_curr;
static float zenH_curr;

//Threads
static pthread_t i2cbus1XenH_id;
static pthread_t i2cbus1YenH_id;
static pthread_t i2cbus1ZenH_id;

//Mutex
static pthread_mutex_t shared_pipe_mutex = PTHREAD_MUTEX_INITIALIZER;

//Initiate private function
void* I2cbus1readXenH_thread();
void* I2cbus1readYenH_thread();
void* I2cbus1readZenH_thread();
int16_t I2cbus1_getRawData(int8_t rawL, int8_t rawH);
float I2cbus1_convertToGForce(int16_t rawData);



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

    pthread_create(&i2cbus1YenH_id, NULL, I2cbus1readYenH_thread, NULL);
    pthread_create(&i2cbus1XenH_id, NULL, I2cbus1readXenH_thread, NULL);
    //pthread_create(&i2cbus1ZenH_id, NULL, I2cbus1readZenH_thread, NULL);
}

void test()
{

}


void I2cbus1Control_join(void)
{
    pthread_join(i2cbus1XenH_id, NULL);
    pthread_join(i2cbus1YenH_id, NULL);
    //pthread_join(i2cbus1ZenH_id, NULL);
}


void I2cbus1Control_cleanup(void)
{
    xenH_curr = 0;
    yenH_curr = 0;
    zenH_curr = 0;

    memset(xen_L_H, 0, sizeof(xen_L_H));
    memset(yen_L_H, 0, sizeof(yen_L_H));
    memset(zen_L_H, 0, sizeof(zen_L_H));
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
void* I2cbus1readXenH_thread()
{  
    while(!isTerminate)
    {
        //Convert raw to G force value
        xen_L_H[0] = I2cbus1Read_OutXL();
        xen_L_H[1] = I2cbus1Read_OutXH();
        xenH_curr = I2cbus1_convertToGForce(I2cbus1_getRawData(xen_L_H[0], xen_L_H[1]));
        
        print("Tilt value: %.2f\n", xenH_curr);
        //Trigger the sound        
        
        sleepForMs(X_FREQUENCY);
    }

    return NULL;
}

// Y_axis move front to back  
void* I2cbus1readYenH_thread()
{
    while(!isTerminate)
    {
        //Convert raw to G force value
        yen_L_H[0] = I2cbus1Read_OutYL();
        yen_L_H[1] = I2cbus1Read_OutYH();
        yenH_curr = I2cbus1_convertToGForce(I2cbus1_getRawData(yen_L_H[0], yen_L_H[1]));

        print("Lean value: %.2f\n", yenH_curr);
        // Left - RED
        // Right - GREEN
        // Center - BLUE 

        sleepForMs(Y_FREQUENCY);
    }

    return NULL;
}

// Z_axis move up to down
void* I2cbus1readZenH_thread()
{
    while(!isTerminate)
    {
        //Convert raw data to G force
        zen_L_H[0] = I2cbus1Read_OutZL();
        zen_L_H[1] = I2cbus1Read_OutZH();
        zenH_curr = I2cbus1_convertToGForce(I2cbus1_getRawData(zen_L_H[0], zen_L_H[1]));

        sleepForMs(Z_FREQUENCY);
    }

    return NULL;
}

int16_t I2cbus1_getRawData(int8_t rawL, int8_t rawH)
{
    return (rawH << 8) | (rawL);
}

float I2cbus1_convertToGForce(int16_t rawData)
{
    return (float)rawData/RESOLUTION_8BITS_SHIFT;
}