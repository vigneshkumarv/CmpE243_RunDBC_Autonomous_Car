// geo_sensors.c
#include "compass.h"

bool read_compass_heading(float* result) {
  char first_reg_address = 0x2;
  uint16_t temp_result;
  uint8_t temp[2];

  if (read_byte_from_i2c_device(COMPASS_ADDRESS, first_reg_address, 2, temp)) {
    temp_result = temp[0] << 8 | temp[1];
    float temp_float = temp_result / 10.0;  // from 3599 to 359.9 for example
    temp_float += 13.244;                   // correct for magnetic declination
    if (temp_float >= 360) {
      temp_float -= 360;
    }
    *result = temp_float;
    return true;
  }
  return false;
}

bool check_calibration_level(uint8_t* result) {
  char calibration_state_address = 0x1E;  // register 30
  bool is_calibration_successful = false;
  if (read_byte_from_i2c_device(COMPASS_ADDRESS, calibration_state_address, 1, result)) {
    (*result) &= ~(0x3f << 2);  // only bit 0 and 1 are looked
    is_calibration_successful = true;
  }
  return is_calibration_successful;
}

void send_debug_msg(can_t* geo_module) {
  uint8_t calibration_result = 7;
  float heading_value = 0;
  // if (check_calibration_level(&calibration_result)) {
  check_calibration_level(&calibration_result);
  DEBUG_data.GEO_COMPASS_Calibration = calibration_result;
  // printf("calibration level: %d \n", DEBUG_data.GEO_COMPASS_Calibration);
  read_compass_heading(&heading_value);
  DEBUG_data.GEO_COMPASS_Heading = heading_value;
  send_can_msg_debug(geo_module, &DEBUG_data);
  //}
}

void storing_compass_calibration_profile(void) {
  unsigned char calibration_values[3] = {0xF0, 0xF5, 0xF6};

  for (int reg_index = 0; reg_index < 3; reg_index++) {
    send_byte_to_i2c_device(COMPASS_ADDRESS, COMPASS_COMMAND_REG, calibration_values[reg_index]);
    delay_ms(20);
  }
}

void erasing_compass_calibration_profile(void) {
  char calibration_values[3] = {0xE0, 0xE5, 0xE2};

  for (int reg_index = 0; reg_index < 3; reg_index++) {
    send_byte_to_i2c_device(COMPASS_ADDRESS, COMPASS_COMMAND_REG, calibration_values[reg_index]);
    delay_ms(20);
  }
}
