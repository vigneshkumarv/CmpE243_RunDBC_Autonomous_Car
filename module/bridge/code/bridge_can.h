/*
 * bridge_can.h
 *
 *  Created on: Apr 26, 2019
 *      Author: lenovo
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
void bridge_if_CAN_is_off_then_reset_1hz(void);

void receive_geo_CAN_data_10z(void);
void geo_distance_and_angle(dbc_msg_hdr_t* geo_distance_and_angle);
void geo_latitude_and_longitude(dbc_msg_hdr_t* geo_latitude_and_longitude);

void bridge_send_start_stop_CAN_10Hz(void);

bool turn_on_car(void);
bool turn_off_car(void);
void turn_car_on_or_off(void);
void check_app_message_delimiter(void);

#endif /* BRIDGE_CAN_H_ */
