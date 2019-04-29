/*
 * bridge_can.h
 *
 *  Created on: Apr 26, 2019
 *      Author: Vignesh
 */

#ifndef BRIDGE_CAN_H_
#define BRIDGE_CAN_H_
#include <stdbool.h>
#include <stdio.h>
#include "can.h"
#include "generated_can/generated_can.h"
#include "string.h"

bool bridge_uart2_init(void);
bool bridge_CAN_init(void);

void is_bridge_CAN_busoff_then_reset_1hz(void);
void receive_CAN_data_10Hz(void);

typedef struct {
  float geo_src_latitude;
  float geo_src_longitude;
  float deflection_angle;
  float distance_from_destination;
} Geo_Data_S;


void geo_distance_and_angle(Geo_Data_S* geo_distance_and_angle);
void geo_latitude_and_longitude(Geo_Data_S* geo_latitude_and_longitude);

void bridge_send_start_stop_CAN_100Hz(void);

bool turn_on_car(void);
bool turn_off_car(void);
void turn_car_on_or_off(void);

#endif /* BRIDGE_CAN_H_ */
