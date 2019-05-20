// geo_sensors.c
#include "compass.h"

bool read_compass_heading(float* result) {
  char first_reg_address = 0x2;
  uint16_t temp_result;
  uint8_t temp[2];

  if (read_byte_from_i2c_device(COMPASS_ADDRESS, first_reg_address, 2, temp)) {
    temp_result = temp[0] << 8 | temp[1];
    float temp_float = temp_result / 10.0;  // from 3599 to 359.9 for example                    // calibration offset
    temp_float += 13.244;                   // correct for magnetic declination
    if (temp_float < 0) {
      temp_float += 360;
    } else if (temp_float >= 360) {
      temp_float -= 360;
    }
    *result = temp_float;
    // printf("heading: %f\n", *result);
    return true;
  }
  return false;
}

bool read_compass_heading_lsm303(float* result) {
  uint8_t lsm303_mag_address = 0x3c;
  const double PI = 3.141592653;
  uint8_t starting_address_x = 0x3;
  uint8_t starting_address_z = 0x5;
  uint8_t starting_address_y = 0x7;
  uint8_t temp[2];
  float temp_float = 0;
  int xMag = 0, yMag = 0;
  bool read_successfulx = false;
  bool read_successfuly = false;

  if (read_byte_from_i2c_device(lsm303_mag_address, starting_address_x, 2, temp)) {
    read_successfulx = true;
    // printf("read x successful\n");
    xMag = (temp[0] * 256 + temp[1]);
    if (xMag > 32767) {
      xMag -= 65536;
    }
  }
  if (read_byte_from_i2c_device(lsm303_mag_address, starting_address_z, 2, temp)) {
    read_successfuly = true;
    // printf("read z successful\n");
  }

  if (read_byte_from_i2c_device(lsm303_mag_address, starting_address_y, 2, temp)) {
    read_successfuly = true;
    // printf("read y successful\n");
    yMag = (temp[0] * 256 + temp[1]);
    if (yMag > 32767) {
      yMag -= 65536;
    }
  }

  if (read_successfulx && read_successfuly) {
    temp_float = atan2(yMag, xMag) * 180 / PI;
    temp_float += 13.244;  // correct for magnetic declination
    if (temp_float < 0) {
      temp_float += 360;
    } else if (temp_float >= 360) {
      temp_float -= 360;
    }
    *result = temp_float;
    printf("heading: %f\n", *result);
    return true;
  }
  return false;
}

void init_lsm303(void) {
  uint8_t lsm303_mag_address = 0x3c;
  uint8_t MR_reg_address = 0x02;
  uint8_t CRA_reg_address = 0x00;
  uint8_t CRB_reg_address = 0x01;
  uint8_t config[2];
  // Select MR register(0x02)
  // Continuous conversion(0x00)
  config[0] = 0x02;
  send_byte_to_i2c_device(lsm303_mag_address, MR_reg_address, config[0]);
  config[1] = 0x00;
  send_byte_to_i2c_device(lsm303_mag_address, MR_reg_address, config[1]);

  // Select CRA register(0x00)
  // Data output rate = 15Hz(0x10)
  config[0] = 0x00;
  send_byte_to_i2c_device(lsm303_mag_address, CRA_reg_address, config[0]);
  config[1] = 0x10;
  send_byte_to_i2c_device(lsm303_mag_address, CRA_reg_address, config[1]);
  // Select CRB register(0x01)
  // Set gain = +/- 4.0g(0x80)
  config[0] = 0x01;
  send_byte_to_i2c_device(lsm303_mag_address, CRB_reg_address, config[0]);
  config[1] = 0x80;
  send_byte_to_i2c_device(lsm303_mag_address, CRB_reg_address, config[1]);
}

bool check_calibration_level(uint8_t* result) {
  char calibration_state_address = 0x1E;  // register 30
  bool is_calibration_successful = false;
  if (read_byte_from_i2c_device(COMPASS_ADDRESS, calibration_state_address, 1, result)) {
    //(*result) &= ~(0x3f << 2);  // only bit 0 and 1 are looked
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

void starting_calibration(void) {
  if (getSwitch(1))  // if button 1 is pressed
  {
    // store calibration profile
    storing_compass_calibration_profile();
  }
  if (getSwitch(2))  // if button 2 is pressed
  {
    // erase calibration profile
    erasing_compass_calibration_profile();
  }
}

void enable_auto_calibration(void) {
  unsigned char calibration_values[3] = {0x98, 0x95, 0x99};

  for (int reg_index = 0; reg_index < 3; reg_index++) {
    send_byte_to_i2c_device(COMPASS_ADDRESS, COMPASS_COMMAND_REG, calibration_values[reg_index]);
    delay_ms(20);
  }
  send_byte_to_i2c_device(COMPASS_ADDRESS, COMPASS_COMMAND_REG, 0x97);  // 0b10010111 auto-cal register sequence
}

void disable_auto_calibration(void) {
  unsigned char calibration_values[3] = {0x98, 0x95, 0x99};

  for (int reg_index = 0; reg_index < 3; reg_index++) {
    send_byte_to_i2c_device(COMPASS_ADDRESS, COMPASS_COMMAND_REG, calibration_values[reg_index]);
    delay_ms(20);
  }
  send_byte_to_i2c_device(COMPASS_ADDRESS, COMPASS_COMMAND_REG, 0x97);  // 0b10000000 auto-cal register sequence
}
