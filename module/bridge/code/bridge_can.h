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
#include "generated_can\generated_can.h"
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

typedef struct {
  uint8_t LeftUltrasonic;
  uint8_t RightUltrasonic;
  uint16_t MiddleUltrasonic;
  uint16_t RearIr;
} Sensor_Data_S;

GEO_COORDINATE_DATA_t geo_source_data;
void receive_parameters(Geo_Data_S* geo_data, Sensor_Data_S* sensor_data_to_android);

void bridge_send_start_stop_CAN_10Hz(void);
void compile_and_send_data(void);
bool turn_on_car(void);
bool turn_off_car(void);
void get_data_from_app(void);
void parse_received_data(char* TX, size_t size_of_tx);

#endif /* BRIDGE_CAN_H_ */
