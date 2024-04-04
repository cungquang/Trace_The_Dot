#include "../include/register_configure.h"

#define I2CDRV_LINUX_BUS0 "/dev/i2c-0"
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"

//14 Segments digits
#define I2C_DEVICE_ADDRESS_DIGIT 0x20

#define REG_DIRA 0x00
#define REG_DIRB 0x01
#define REG_OUTA 0x14
#define REG_OUTB 0x15


//Register address & value for each number display from 0 - 9
#define OXOO_0 0xd0
#define OXO1_0 0xa1
#define OXOO_1 0x00
#define OXO1_1 0xe0
#define OXOO_2 0x98
#define OXO1_2 0x83
#define OXOO_3 0x18
#define OXO1_3 0xa3
#define OXOO_4 0x48
#define OXO1_4 0xe2
#define OXOO_5 0x58
#define OXO1_5 0x23
#define OXOO_6 0xd8
#define OXO1_6 0x23
#define OXOO_7 0x10
#define OXO1_7 0xe2
#define OXOO_8 0xd8
#define OXO1_8 0xa3
#define OXOO_9 0x58
#define OXO1_9 0xa3

//Accelerometer
#define I2C_DEVICE_ADDRESS_ACC 0x18

#define REG_CTRL_REG1 0x20
#define REG_OUT_X_L 0x28
#define REG_OUT_X_H 0x29
#define REG_OUT_Y_L 0x2A
#define REG_OUT_Y_H 0x2B
#define REG_OUT_Z_L 0x2C
#define REG_OUT_Z_H 0x2D

//File description
static int i2c1_FileDesc_Digits;
static int i2c1_FileDesc_Accelerometer;


/*
#########################
#        PUBLIC         #
#########################
*/


////////////////////////// INIT OPERATION //////////////////////////

void I2cbus1_init()
{
    //Enable the bus1 - 0x18
    i2c1_FileDesc_Digits = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS_DIGIT);
    i2c1_FileDesc_Accelerometer = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS_ACC);

    //Pin9_17 not yet configure -> configure
    if(!isI2cConfigure_p917())
    {
        initI2c_p917();
    }

    //Pin9_18 not yet configure -> configure
    if(!isI2cConfigure_p918())
    {
        initI2c_p918();
    }

    //Pin8_11 not yet configure -> configure
    if(!isI2cConfigure_p811())
    {
        initI2c_p811();
    }
}

int I2c1FileDescDigit_get(void)
{
    return i2c1_FileDesc_Digits;
}

int I2c1FileDescAccelerometer_get(void)
{
    return i2c1_FileDesc_Accelerometer;
}

void I2c1FileDescDigit_set(int newI2c1FileDesc)
{
    i2c1_FileDesc_Digits = newI2c1FileDesc;
}

void I2c1FileDescAccelerometer_set(int newI2c1FileDesc)
{
    i2c1_FileDesc_Accelerometer = newI2c1FileDesc;
}



///////////////////////// WRITE 14 SEGMENTS OPERATION /////////////////////////


void I2cbus1Write_No0(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, OXOO_0);
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, OXO1_0);
}

void I2cbus1Write_No1(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, OXOO_1);
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, OXO1_1);
}

void I2cbus1Write_No2(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, OXOO_2);
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, OXO1_2);
}

void I2cbus1Write_No3(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, OXOO_3);
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, OXO1_3);
}

void I2cbus1Write_No4(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, OXOO_4);
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, OXO1_4);
}

void I2cbus1Write_No5(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, OXOO_5);
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, OXO1_5);
}

void I2cbus1Write_No6(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, OXOO_6);
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, OXO1_6);
}

void I2cbus1Write_No7(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, OXOO_7);
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, OXO1_7);
}

void I2cbus1Write_No8(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, OXOO_8);
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, OXO1_8);
}

void I2cbus1Write_No9(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, OXOO_9);
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, OXO1_9);
}


////////////////////////// READ ACCELEROMETER OPERATION //////////////////////////


void I2cbus1Write_Reg1(unsigned char value)
{
    if(!i2c1_FileDesc_Accelerometer)
    {
        printf("ERROR: The bus was not iniated\n");
        exit(EXIT_FAILURE);
    }

    //Write to the CTRL_REG1
    writeI2cReg(i2c1_FileDesc_Accelerometer, REG_CTRL_REG1, value);
}

unsigned char I2cbus1Read_Reg1()
{
    if(!i2c1_FileDesc_Accelerometer)
    {
        printf("ERROR: The bus was not iniated\n");
        exit(EXIT_FAILURE);
    }

    //Read from reg1
    return readI2cReg(i2c1_FileDesc_Accelerometer, REG_CTRL_REG1);
}

unsigned char I2cbus1Read_OutXL()
{
    if(!i2c1_FileDesc_Accelerometer)
    {
        printf("ERROR: The bus was not iniated\n");
        exit(EXIT_FAILURE);
    }

    //Read from reg1
    return readI2cReg(i2c1_FileDesc_Accelerometer, REG_OUT_X_L);
}

unsigned char I2cbus1Read_OutXH()
{
    if(!i2c1_FileDesc_Accelerometer)
    {
        printf("ERROR: The bus was not iniated\n");
        exit(EXIT_FAILURE);
    }

    //Read from reg1
    return readI2cReg(i2c1_FileDesc_Accelerometer, REG_OUT_X_H);
}

unsigned char I2cbus1Read_OutYL()
{
    if(!i2c1_FileDesc_Accelerometer)
    {
        printf("ERROR: The bus was not iniated\n");
        exit(EXIT_FAILURE);
    }

    //Read from reg1
    return readI2cReg(i2c1_FileDesc_Accelerometer, REG_OUT_Y_L);
}

unsigned char I2cbus1Read_OutYH()
{
    if(!i2c1_FileDesc_Accelerometer)
    {
        printf("ERROR: The bus was not iniated\n");
        exit(EXIT_FAILURE);
    }

    //Read from reg1
    return readI2cReg(i2c1_FileDesc_Accelerometer, REG_OUT_Y_H);
}

unsigned char I2cbus1Read_OutZL()
{
    if(!i2c1_FileDesc_Accelerometer)
    {
        printf("ERROR: The bus was not iniated\n");
        exit(EXIT_FAILURE);
    }

    //Read from reg1
    return readI2cReg(i2c1_FileDesc_Accelerometer, REG_OUT_Z_L);
}

unsigned char I2cbus1Read_OutZH()
{
    if(!i2c1_FileDesc_Accelerometer)
    {
        printf("ERROR: The bus was not iniated\n");
        exit(EXIT_FAILURE);
    }

    //Read from reg1
    return readI2cReg(i2c1_FileDesc_Accelerometer, REG_OUT_Z_H);
}


/*
#########################
#       PRIVATE         #
#########################
*/
