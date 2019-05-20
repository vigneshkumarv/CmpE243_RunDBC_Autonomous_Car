// Functions for compass

#ifndef COMPASS_H__
#define COMPASS_H__

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "can.h"
#include "generated_can.h"
#include "geo_can.h"
#include "i2c_wrapper.h"
#include "switches_wrapper.h"
#include "utilities.h"

#define COMPASS_ADDRESS 0xC0
#define COMPASS_COMMAND_REG 0x0
GEO_DATA_t geo_data;
GEO_COORDINATE_DATA_t geo_coordinate_data;

// read heading from compass.
// return true is reading is successful
// result will be between 0 - 3599, representing 0-359.9°.
bool read_compass_heading(float* result);

// this function checks the calibration level of cmps12.
// returns true if check is successful
// bits 0 and 1 of result reflect the calibration status (0 un-calibrated, 3 fully calibrated)
bool check_calibration_level(uint8_t* result);
void starting_calibration(void);
void enable_auto_calibration(void);
void disable_auto_calibration(void);
void send_debug_msg(can_t* geo_module);

// functions used for storing and erasing calibration profile
// different from cmps11, CMPS12 is continually auto calibrating
// after erasing profile, compass reverts back to default state
void storing_compass_calibration_profile(void);
void erasing_compass_calibration_profile(void);

// lsm303 code
// void init_lsm303(void);
// bool read_compass_heading_lsm303(float* result);

#endif  // COMPASS_H__
