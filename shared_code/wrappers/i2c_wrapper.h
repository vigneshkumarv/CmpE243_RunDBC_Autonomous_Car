// ls_wrapper.h

#ifndef I2C_WRAPPER_H__
#define I2C_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

bool send_byte_to_i2c_device(unsigned char dev_address, unsigned char reg_to_write, unsigned char byte_to_write);
bool read_byte_from_i2c_device(unsigned char dev_address, unsigned char first_reg_to_read, unsigned int size_to_read,
                               unsigned char* value);

#ifdef __cplusplus
}
#endif
#endif /* I2C_WRAPPER_H__ */
