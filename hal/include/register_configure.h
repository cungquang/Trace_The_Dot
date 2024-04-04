#ifndef _REGISTER_CONFIGURE_H_
#define _REGISTER_CONFIGURE_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "./i2c_configure.h"

//Init opeartion
void I2cbus1_init();
int I2c1FileDescDigit_get(void);
int I2c1FileDescAccelerometer_get(void);
void I2c1FileDescDigit_set(int newI2c1FileDesc);
void I2c1FileDescAccelerometer_set(int newI2c1FileDesc);


//Write 14 segments digits
void I2cbus1Write_No0(void);
void I2cbus1Write_No1(void);
void I2cbus1Write_No2(void);
void I2cbus1Write_No3(void);
void I2cbus1Write_No4(void);
void I2cbus1Write_No5(void);
void I2cbus1Write_No6(void);
void I2cbus1Write_No7(void);
void I2cbus1Write_No8(void);
void I2cbus1Write_No9(void);


//Write operation
void I2cbus1Write_Reg1(unsigned char value);


//Read operation for REG1, OUTXL, OUTXH, OUTYL, OUTYH, OUTZL, OUTZH
unsigned char I2cbus1Read_Reg1();
unsigned char I2cbus1Read_OutXL();
unsigned char I2cbus1Read_OutXH();
unsigned char I2cbus1Read_OutYL();
unsigned char I2cbus1Read_OutYH();
unsigned char I2cbus1Read_OutZL();
unsigned char I2cbus1Read_OutZH();

#endif