#include "../include/i2c.h"
#include <iostream>

// Define device address
// It is a better idea to include all the addresses in a header file
#define DEVICE_ADDR 	0x19

// Define register address
#define CTRL_REG1		0x10
#define STATUS_REG		0x12

using namespace std;

int main(){
	// Instantiate the I2c Object
	myI2C *i2cptr = new myI2C();
	
	int value = 10;
	
	i2cptr->Send_I2C_Byte(DEVICE_ADDR,CTRL_REG1,value); 							// Example send data
	
	value = i2cptr->Read_I2C_Byte(DEVICE_ADDR, STATUS_REG);							// Read single byte
	
	i2cptr->Read_Multi_Byte(DEVICE_ADDR, 0x80 | STATUS_REG); 			// Example read multiple data
	// Output data will be stored in i2cptr->I2C_RD_Buf. Check i2c.cpp for more details
	
	return 0;
}
