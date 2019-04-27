// the c file linked to this header file goes over the entire sensor reading and sending steps
#ifndef READ_AND_SEND_H_
#define READ_AND_SEND_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "generated_can.h"
#include "can.h"
#include "car_sensors.h"

// this function reads all sensors
void read_left_right_ultrasonic_sensors(void);
void read_middle_rear_sensors(void);
void read_left_right_bumper_sensors(void);
void send_can_msg(can_t* sensor_module);
void send_heartbeat_msg(can_t* sensor_module);

#endif
