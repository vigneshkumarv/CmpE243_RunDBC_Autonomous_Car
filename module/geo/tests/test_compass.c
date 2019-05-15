#include "unity.h"

#include <stdbool.h>
#include <stdint.h>
#include "compass.h"
#include "queue.h"
#include "Mocki2c_wrapper.h"
#include "Mockcan.h"
#include "Mockutilities.h"

bool flag = false;
float var=0;
float* result = &var;


void setUp(void) {
}
void tearDown(void) {
}

void test_read_compass_heading(void)
{

    char first_reg_address = 0x2;
    // uint16_t temp_result;
    uint8_t temp[2];
    read_byte_from_i2c_device_ExpectAndReturn(0xC0,first_reg_address, 2, temp,true);
    flag = read_compass_heading(result);
    TEST_ASSERT_TRUE(flag);

    read_byte_from_i2c_device_ExpectAndReturn(0xC0,first_reg_address, 2, temp,false);
    flag = read_compass_heading(result);
    TEST_ASSERT_FALSE(flag);
}

void test_check_calibration_level(void)
{

    char calibration_state_address = 0x1E;  // register 30
    uint8_t result_arg = 0;
    uint8_t *p =&result_arg;
    read_byte_from_i2c_device_ExpectAndReturn(0xC0, calibration_state_address, 1, p, true);
    flag = check_calibration_level(p);
    TEST_ASSERT_TRUE(flag);

    read_byte_from_i2c_device_ExpectAndReturn(0xC0, calibration_state_address, 1, p, false);
    flag = check_calibration_level(p);
    TEST_ASSERT_FALSE(flag);

}

void test_storing_compass_calibration_profile(void)
{
    unsigned char calibration_values[3] = {0xF0, 0xF5, 0xF6};

    for (int reg_index = 0; reg_index < 3; reg_index++)
    {
        send_byte_to_i2c_device_ExpectAndReturn(0XC0, 0x0, calibration_values[reg_index],true);
        delay_ms_Expect(20);
    }
    storing_compass_calibration_profile();
}

void test_erasing_compass_calibration_profile(void)
{
    char calibration_values[3] = {0xE0, 0xE5, 0xE2};
    for (int reg_index = 0; reg_index < 3; reg_index++)
        {
            send_byte_to_i2c_device_ExpectAndReturn(0XC0, 0x0, calibration_values[reg_index],true);
            delay_ms_Expect(20);
        }

    erasing_compass_calibration_profile();
}

