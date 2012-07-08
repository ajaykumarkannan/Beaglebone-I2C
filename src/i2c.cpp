#include "../include/i2c.h"

myI2C::myI2C(){
	this->i2cOpen();
}

myI2C::~myI2C(){
	this->i2cClose();
}

// open the Linux device
void myI2C::i2cOpen()
{
	g_i2cFile = open("/dev/i2c-3", O_RDWR);
	if (g_i2cFile < 0) {
		perror("i2cOpen");
		exit(1);
	}
}

// close the Linux device
void myI2C::i2cClose()
{
	close(g_i2cFile);
}

// set the I2C slave address for all subsequent I2C device transfers
void myI2C::i2cSetAddress(int address)
{
	if (ioctl(g_i2cFile, I2C_SLAVE, address) < 0) {
		perror("i2cSetAddress");
		exit(1);
	}
}


void myI2C::Send_I2C_Byte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, unsigned char Data){
	i2cSetAddress(DEVICE_ADDR);
	
	I2C_WR_Buf[0] = Reg_ADDR;
	I2C_WR_Buf[1] = Data;

	if(write(g_i2cFile, I2C_WR_Buf, 2) != 2) {
		perror("Write Error");
	}
}


unsigned char myI2C::Read_I2C_Byte(unsigned char DEVICE_ADDR,unsigned char Reg_ADDR){
	I2C_WR_Buf[0] = Reg_ADDR;
	
	i2cSetAddress(DEVICE_ADDR);
	if(write(g_i2cFile, I2C_WR_Buf, 1) != 1) {
		perror("Write Error");
	}
	i2cSetAddress(DEVICE_ADDR);	
	if(read(g_i2cFile, I2C_RD_Buf, 1) !=1){
		perror("Read Error");
	}
	
	return I2C_RD_Buf[0];
}

unsigned char myI2C::Read_Multi_Byte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR){
	I2C_WR_Buf[0] = Reg_ADDR;
	
	i2cSetAddress(DEVICE_ADDR);
	if(write(g_i2cFile, I2C_WR_Buf, 1) != 1) {
		perror("Write Error");
	}
	i2cSetAddress(DEVICE_ADDR);	
	if(read(g_i2cFile, I2C_RD_Buf, 7) !=7){
		perror("Read Error");
	}
		
	return I2C_RD_Buf[0];
}
