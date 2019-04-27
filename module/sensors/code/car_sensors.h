// this .h file provides functions to read sensor values
#ifndef CAR_SENSORS_H_
#define CAR_SENSORS_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "generated_can.h"
#include "queue.h"
#include "sensor_wrapper.h"
#include "utilities.h"

SENSOR_DATA_t sensor_data;

typedef enum {
  left = 0,
  middle = 1,
  right = 2,
  rear = 3,
} sensor_position;

// initialization of sensors
void init_sensors(void);
void init_bump_sensors(void);
void init_ir_sensor(void);
void init_speed_sensor(void);
void calibrate_sensors(sensor_position whichSensor);

// bump sensor (left and right)
void bumper_sensor_read(sensor_position whichSensor);
void distance_sensor_read(sensor_position whichSensor);

#endif
