#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#define MAX_BUFFER_SIZE					16

class myI2C {
	int g_i2cFile;
public:
	myI2C();
	~myI2C();
	
	// Public Variables
	unsigned char I2C_WR_Buf[MAX_BUFFER_SIZE];
	unsigned char I2C_RD_Buf[MAX_BUFFER_SIZE];
	
	// Initialize Functions
	void i2cOpen();
	void i2cClose();
	void i2cSetAddress(int address);
	
	// Read/Write Functions
	void Send_I2C_Byte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR, unsigned char Data);
	unsigned char Read_I2C_Byte(unsigned char DEVICE_ADDR,unsigned char Reg_ADDR);
	unsigned char Read_Multi_Byte(unsigned char DEVICE_ADDR, unsigned char Reg_ADDR);
};
