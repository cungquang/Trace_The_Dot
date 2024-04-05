#include "../include/digits_control.h"

#define SWITCH_TIME 5

static int isTerminated;

//Resources
static int points_count;
static int point_leftDigit;
static int point_rightDigit;

//Threads
static pthread_t digit_displayThreadId;

//Mutex
static pthread_mutex_t shared_section_mutex = PTHREAD_MUTEX_INITIALIZER;

//Initiate private
static void *Digits_displayThread(); 
static void Digits_selectPattern(int digit);

/*
#########################
#        PUBLIC         #
#########################
*/

void Digits_init(void)
{
    //Create thread
    pthread_create(&digit_displayThreadId, NULL, Digits_displayThread, NULL);
}

void Digits_join(void)
{
    pthread_join(digit_displayThreadId, NULL);
}

void Digits_cleanUp(void)
{
    //turn off both digits
    I2cbus1_disableLeftDigit();
    I2cbus1_disableRightDigit();
}

void Digits_setTerminated(void)
{
    isTerminated = 1;
}

void Digits_setValueToDisplay(int displayValue)
{
    //Access critical section
    pthread_mutex_lock(&shared_section_mutex);
    points_count = displayValue;
    pthread_mutex_unlock(&shared_section_mutex);

    //if the dips larger than 99 -> set to 99
    points_count = points_count > 99? 99 : points_count;

    //Convert dips to string
    if(points_count > 9)
    {
        char number[3];
        snprintf(number, sizeof(number), "%d", points_count);
        
        point_leftDigit = number[0] - '0';
        point_rightDigit = number[1] - '0';
        printf("left_digit: %d   right_digit: %d\n", point_leftDigit, point_rightDigit);
    } else{
        char number[2];
        snprintf(number, sizeof(number), "%d", points_count);

        point_leftDigit = 0;
        point_rightDigit = number[0] - '0';
        // printf("left_digit: %d   right_digit: %d\n", point_leftDigit, point_rightDigit);
    }    
}


/*
#########################
#        PRIVATE        #
#########################
*/


static void *Digits_displayThread() 
{
    while(!isTerminated)
    {
        //turn off both digits
        I2cbus1_disableRightDigit();
        I2cbus1_disableLeftDigit();

        //display pattern for left digit
        Digits_selectPattern(point_leftDigit);
        I2cbus1_enableLeftDigit();
        sleepForMs(SWITCH_TIME);

        //turn off both digits
        I2cbus1_disableRightDigit();
        I2cbus1_disableLeftDigit();

        //display pattern for right digit
        Digits_selectPattern(point_rightDigit);
        I2cbus1_enableRightDigit();
        sleepForMs(SWITCH_TIME);
    }

    return NULL;
}

static void Digits_selectPattern(int digit)
{   
    switch(digit)
    {
        case 0:
            I2cbus1Write_No0();
            break;
        case 1:
            I2cbus1Write_No1();
            break;
        case 2:
            I2cbus1Write_No2();
            break;
        case 3:
            I2cbus1Write_No3();
            break;
        case 4:
            I2cbus1Write_No4();
            break;
        case 5:
            I2cbus1Write_No5();
            break;
        case 6:
            I2cbus1Write_No6();
            break;
        case 7:
            I2cbus1Write_No7();
            break;
        case 8:
            I2cbus1Write_No8();
            break;
        case 9:
            I2cbus1Write_No9();
            break;
        default:
            perror("Invalid input digit for display");
            exit(1);
    }
}