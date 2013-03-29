#include "../include/i2c.h"
#include <iostream>
using namespace std;

myI2C::myI2C(){
	this->i2cOpen();
}

myI2C::~myI2C(){
	this->i2cClose();
}

// open the Linux device
void myI2C::i2cOpen()
{
	//cout << "beagle-i2c opening /dev/i2c-3... ";
	g_i2cFile = open("/dev/i2c-3", O_RDWR);
	if (g_i2cFile < 0) {
		perror("i2cOpen in myI2C::i2cOpen");
		exit(1);
	}
//	else cout << "OK"<<endl;
}

// close the Linux device
void myI2C::i2cClose()
{
	close(g_i2cFile);
}

// set the I2C slave address for all subsequent I2C device transfers
void myI2C::i2cSetAddress(unsigned char address)
{
	//cout << "beagle-i2c setting address 0x"<< hex <<(int)address <<"... ";
	if (ioctl(g_i2cFile, I2C_SLAVE, address) < 0) {
		perror("i2cSetAddress error in myI2C::i2cSetAddress");
		exit(1);
	}
//	else cout << "OK" <<endl;
}


void myI2C::Send_I2C_Byte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, unsigned char Data){
	i2cSetAddress(DEVICE_ADDR);
	//cout << "beagle-i2c writing 0x"<< hex << (int)Data <<" to 0x"<<hex <<(int)DEVICE_ADDR << ", reg 0x" <<hex<<(int)Reg_ADDR <<"... ";
	I2C_WR_Buf[0] = Reg_ADDR;
	I2C_WR_Buf[1] = Data;

	if(write(g_i2cFile, I2C_WR_Buf, 2) != 2) {
		perror("Write Error in myI2C::Send_I2C_Byte");
	}
//	else cout << "OK";

}


unsigned char myI2C::Read_I2C_Byte(unsigned char DEVICE_ADDR,unsigned char Reg_ADDR){
	I2C_WR_Buf[0] = Reg_ADDR;
	
	i2cSetAddress(DEVICE_ADDR);
	if(write(g_i2cFile, I2C_WR_Buf, 1) != 1) {
		perror("Write Error in myI2C::Read_I2C_Byte");
	}
	i2cSetAddress(DEVICE_ADDR);	
	if(read(g_i2cFile, I2C_RD_Buf, 1) !=1){
		perror("Read Error myI2C::Read_I2C_Byte");
	}
	
	return I2C_RD_Buf[0];
}

unsigned char myI2C::Read_Multi_Byte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, size_t n){
	I2C_WR_Buf[0] = Reg_ADDR;
	
	i2cSetAddress(DEVICE_ADDR);
	ssize_t s = write(g_i2cFile, I2C_WR_Buf, 1);
	if( s != 1) {
		cout << "Wanted to write " << 1 << " byte, but instead wrote " << s << ". " <<endl;
		perror("Write Error in myI2C::Read_Multi_Byte");
	}
	i2cSetAddress(DEVICE_ADDR);	
	ssize_t t = read(g_i2cFile, I2C_RD_Buf, n);
	if( t != n)
	{
		cout << "Wanted to read " << n << " bytes, but instead got " << t << ". " <<endl;
		perror("Read Error in myI2C::Read_Multi_Byte");
	}
		
	return I2C_RD_Buf[0];
}
