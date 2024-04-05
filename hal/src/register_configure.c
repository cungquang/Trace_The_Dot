#include "../include/register_configure.h"

#define I2CDRV_LINUX_BUS0 "/dev/i2c-0"
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"

//14 Segments digits
#define ENABLE_61 "echo 1 > /sys/class/gpio/gpio61/value"
#define DISABLE_61 "echo 0 > /sys/class/gpio/gpio61/value"

#define ENABLE_44 "echo 1 > /sys/class/gpio/gpio44/value"
#define DISABLE_44 "echo 0 > /sys/class/gpio/gpio44/value"

#define I2C_DEVICE_ADDRESS_DIGIT 0x20

#define REG_DIRA 0x02
#define REG_DIRB 0x03
#define REG_OUTA 0x00
#define REG_OUTB 0x01

//Register address & value for each number display from 0 - 9
#define OXOO_0 0xd0
#define OXO1_0 0xa1
#define OXOO_1 0xc0
#define OXO1_1 0x00
#define OXOO_2 0x98
#define OXO1_2 0x83
#define OXOO_3 0x18
#define OXO1_3 0xa3
#define OXOO_4 0x22
#define OXO1_4 0xc8
#define OXOO_5 0x58
#define OXO1_5 0x23
#define OXOO_6 0x58
#define OXO1_6 0xa3
#define OXOO_7 0xc8
#define OXO1_7 0x01
#define OXOO_8 0xd8
#define OXO1_8 0xa3
#define OXOO_9 0xd8
#define OXO1_9 0x23

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

//Initiate private
void I2cbus1Write_outDir(void);


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

    //Pin8_12
    initI2c_p812();
    
    //Pin8_15
    initI2c_p815();

    //Write out into Directory
    I2cbus1Write_outDir();
}

void I2c1FileDescDigit_close(void)
{
    close(i2c1_FileDesc_Digits);
}

void I2c1FileDescAccelerometer_close(void)
{
    close(i2c1_FileDesc_Accelerometer);
}

///////////////////////// WRITE 14 SEGMENTS OPERATION /////////////////////////

void I2cbus1_enableRightDigit(void)
{
    system(ENABLE_61);
}

void I2cbus1_disableRightDigit(void)
{
    system(DISABLE_61);
}

void I2cbus1_enableLeftDigit(void)
{
    system(ENABLE_44);
}

void I2cbus1_disableLeftDigit(void)
{
    system(DISABLE_44);
}

void I2cbus1Write_No0(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTA, OXOO_0);
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTB, OXO1_0);
}

void I2cbus1Write_No1(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTA, OXOO_1);
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTB, OXO1_1);
}

void I2cbus1Write_No2(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTA, OXOO_2);
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTB, OXO1_2);
}

void I2cbus1Write_No3(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTA, OXOO_3);
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTB, OXO1_3);
}

void I2cbus1Write_No4(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTA, OXOO_4);
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTB, OXO1_4);
}

void I2cbus1Write_No5(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTA, OXOO_5);
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTB, OXO1_5);
}

void I2cbus1Write_No6(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTA, OXOO_6);
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTB, OXO1_6);
}

void I2cbus1Write_No7(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTA, OXOO_7);
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTB, OXO1_7);
}

void I2cbus1Write_No8(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTA, OXOO_8);
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTB, OXO1_8);
}

void I2cbus1Write_No9(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTA, OXOO_9);
    writeI2cReg(i2c1_FileDesc_Digits, REG_OUTB, OXO1_9);
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


void I2cbus1Write_outDir(void)
{
    writeI2cReg(i2c1_FileDesc_Digits, REG_DIRA, 0x00);
	writeI2cReg(i2c1_FileDesc_Digits, REG_DIRB, 0x00);
}