#include "../include/i2cbus1_control.h"
#include "../include/neoPixelRGBW-Linux.h"

#define TRIGGER_BIT 0x27
#define BUFFER_SIZE 2
#define RESOLUTION_8BITS_SHIFT 16000
#define SELECT_SCALE 2
#define XY_FREQUENCY 100

//LEAN BOUND
#define LEAN_DEBOUNCE_THRESHOLD 6
#define LEAN_CENTER_UPPER_BOUND 0.15
#define LEAN_CENTER_LOWER_BOUND -0.15

//TILT BOUND
#define TILT_DEBOUNCE_THRESHOLD 4
#define TILT_CENTER_UPPER_BOUND 0.15
#define TILT_CENTER_LOWER_BOUND -0.15

//CENTER COLOR
#define CENTER_COLOR      0x00000f00

//Operation
static int isTerminate = 0;

//Focus point
static int dot_up;
static int dot_middle;
static int dot_down;

//Display colors:
static uint32_t color_background;
static uint32_t color_up;
static uint32_t color_middle;
static uint32_t color_down;

//Raw data G-force
static unsigned char xen_L_H[BUFFER_SIZE];
static unsigned char yen_L_H[BUFFER_SIZE];

//Converted G-force value
static float xenH_curr;
static float yenH_curr;

//Prevent bounce back
static long leanDebounce_count;
static int isLeaned;
static long tiltDebounce_count;
static int isTilt;

//Threads
static pthread_t i2cbus1XYenH_id;

//Mutex
static pthread_mutex_t shared_pipe_mutex = PTHREAD_MUTEX_INITIALIZER;

//Initiate private function
static void* I2cbus1readXYenH_thread();
static int16_t I2cbus1_getRawData(int8_t rawL, int8_t rawH);
static float I2cbus1_convertToGForce(int16_t rawData);
static void lean_preventDebounceToCenter(float lean_curr, uint32_t * background);
static void tilt_preventDebounceToCenter(float tilt_curr, int *dotUp, int *dotMiddle, int *dotDown);

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
        // Convert raw to G force value
        // X value: LEFT - RIGHT
        xen_L_H[0] = I2cbus1Read_OutXL();
        xen_L_H[1] = I2cbus1Read_OutXH();
        xenH_curr = I2cbus1_convertToGForce(I2cbus1_getRawData(xen_L_H[0], xen_L_H[1]));

        // Y value: UP - DOWN
        yen_L_H[0] = I2cbus1Read_OutYL();
        yen_L_H[1] = I2cbus1Read_OutYH();
        yenH_curr = I2cbus1_convertToGForce(I2cbus1_getRawData(yen_L_H[0], yen_L_H[1]));

        printf("xenH-lean: %0.2f     xen_L_XL: %d      xen_L_XH: %d \n", xenH_curr, xen_L_H[0], xen_L_H[1]);

        // Critical section
        pthread_mutex_lock(&shared_pipe_mutex);

        // Get X value => color_background
        lean_preventDebounceToCenter(xenH_curr, &color_background);
        getColor_focusPoint(&color_background, &color_up, &color_middle, &color_down);

        // Get dot position
        tilt_preventDebounceToCenter(yenH_curr, &dot_up, &dot_middle, &dot_down);

        // Away from center
        if(isTilt)
        {
            setColor_background(0);
            setColor_ithPosition(color_up, dot_up);
            setColor_ithPosition(color_middle, dot_middle);
            setColor_ithPosition(color_down, dot_down);
        }   
        else
        {
            setColor_background(color_background);
        }

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

static void lean_preventDebounceToCenter(float lean_curr, uint32_t * background)
{  
    // Not yet lean
    if(isLeaned == 0)
    {
        //Update background color
        getColor_background(lean_curr, background);

        //Change lean status
        if(color_background != CENTER_COLOR)
        {
            isLeaned = 1;
        }
    }
    // Already lean
    else 
    {
        // Count (continuously) debounce
        if(lean_curr >= LEAN_CENTER_LOWER_BOUND && lean_curr <= LEAN_CENTER_LOWER_BOUND)
        {
            leanDebounce_count++;
        }
        else{
            // Reset debounce
            leanDebounce_count = 0;

            // Update the latest color
            getColor_background(lean_curr, background);
        }

        // Meet threshold
        if(leanDebounce_count > LEAN_DEBOUNCE_THRESHOLD)
        {
            isLeaned = 0;
            leanDebounce_count = 0;
            // Update the latest color
            getColor_background(lean_curr, background);
        }
    }
}


static void tilt_preventDebounceToCenter(float tilt_curr, int *dotUp, int *dotMiddle, int *dotDown)
{
    // Not yet tilt
    if(isTilt == 0)
    {
        // Get Y value => dot_up & dot_middle & dot_downdd
        getPosition_focusPoint(tilt_curr, dotUp, dotMiddle, dotDown, TILT_CENTER_UPPER_BOUND, TILT_CENTER_LOWER_BOUND);

        //Change lean status
        if(dotUp != 0 || dotMiddle != 0 || dotDown != 0)
        {
            isTilt = 1;
        }
    }
    // Already tilt
    else 
    {
        // Count (continuously) debounce
        if(tilt_curr >= TILT_CENTER_LOWER_BOUND && tilt_curr <= TILT_CENTER_UPPER_BOUND)
        {
            tiltDebounce_count++;
        }
        else{
            // Reset debounce
            tiltDebounce_count = 0;

            // Get Y value => dot_up & dot_middle & dot_downdd
            getPosition_focusPoint(tilt_curr, dotUp, dotMiddle, dotDown, TILT_CENTER_UPPER_BOUND, TILT_CENTER_LOWER_BOUND);
        }

        // Meet threshold
        if(tiltDebounce_count > TILT_DEBOUNCE_THRESHOLD)
        {
            isTilt = 0;
            tiltDebounce_count = 0;

            // Get Y value => dot_up & dot_middle & dot_downdd
            getPosition_focusPoint(tilt_curr, dotUp, dotMiddle, dotDown, TILT_CENTER_UPPER_BOUND, TILT_CENTER_LOWER_BOUND);
        }
    }
}