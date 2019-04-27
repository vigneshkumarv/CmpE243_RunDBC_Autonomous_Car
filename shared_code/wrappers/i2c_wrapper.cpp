// I2C_wrapper.cpp

#include "i2c_wrapper.h"
#include "i2c2.hpp"


bool send_byte_to_i2c_device(unsigned char dev_address, unsigned char reg_to_write, unsigned char byte_to_write)
{
    return (I2C2::getInstance().writeReg(dev_address, reg_to_write, byte_to_write));
}

bool read_byte_from_i2c_device(unsigned char dev_address, unsigned char first_reg_to_read, unsigned int size_to_read, unsigned char * value)
{
    return (I2C2::getInstance().readRegisters(dev_address, first_reg_to_read, value, size_to_read));
}
