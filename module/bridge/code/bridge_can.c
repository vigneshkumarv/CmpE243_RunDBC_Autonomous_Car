/*
 * bridge_can.c
 *
 *  Created on: Apr 26, 2019
 *      Author: Vignesh
 */

#include "bridge_can.h"
#include "uart0_min.h"
#include "uart_wrapper.h"

#define SIZE 50
#define ON "CARON"
#define OFF "CAROFF"

can_msg_t geo_can_msg = {0}, on_off_can_msg = {0}, motor_can_msg = {0};
GEO_COORDINATE_DATA_t geo_source_data = {0};
GEO_DATA_t geo_distance_and_angle_data = {0};
BRIDGE_DATA_t on_off_cmd = {0};
dbc_msg_hdr_t geo_can_msg_hdr, on_off_msg_hdr, motor_steer_speed_direction;
Geo_Data_S to_android = {0};

char RX_buffer[SIZE] = {0};
char TX_buffer[SIZE] = {0};
static int bufferindex = 0;

bool bridge_uart2_init(void) { return uart2_init(9600, 32, 32); }

bool bridge_CAN_init(void) {
  CAN_init(can1, 100, 32, 32, NULL, NULL);
  CAN_reset_bus(can1);
  CAN_bypass_filter_accept_all_msgs();
  return true;
}

void is_bridge_CAN_busoff_then_reset_1hz(void) {
  if (CAN_is_bus_off(can1)) {
    CAN_reset_bus(can1);
  }
}

// decode different messages through a struct pointer and concatenate as required.
void receive_CAN_data_10Hz(void) {
  while (CAN_rx(can1, &geo_can_msg, 0)) {
    geo_can_msg_hdr.dlc = geo_can_msg.frame_fields.data_len;
    geo_can_msg_hdr.mid = geo_can_msg.msg_id;
    geo_distance_and_angle(&to_android);
    geo_latitude_and_longitude(&to_android);
    //~ADLG#

    snprintf(RX_buffer, sizeof(RX_buffer), "~A%.2fD%0.2fL%fG%f#", to_android.deflection_angle,
             to_android.distance_from_destination, to_android.geo_src_latitude, to_android.geo_src_longitude);
    uart2_putLine(RX_buffer, 0);
  }
}

void geo_distance_and_angle(Geo_Data_S* geo_distance_and_angle) {
  // mid of geo data (distance and angle) is 769
  if (dbc_decode_GEO_DATA(&geo_distance_and_angle_data, geo_can_msg.data.bytes, &geo_can_msg_hdr)) {
    geo_distance_and_angle->deflection_angle = geo_distance_and_angle_data.GEO_DATA_Angle;
    geo_distance_and_angle->distance_from_destination = geo_distance_and_angle_data.GEO_DATA_Distance;
  }
}

void geo_latitude_and_longitude(Geo_Data_S* geo_latitude_and_longitude) {
  // mid of geo data (latitude and longitude) is 771
  if (dbc_decode_GEO_COORDINATE_DATA(&geo_source_data, geo_can_msg.data.bytes, &geo_can_msg_hdr)) {
    geo_latitude_and_longitude->geo_src_latitude = geo_source_data.GEO_DATA_Latitude;
    geo_latitude_and_longitude->geo_src_longitude = geo_source_data.GEO_DATA_Longitude;
  }
}

void bridge_send_start_stop_CAN_100Hz(void) { turn_car_on_or_off(); }

void turn_car_on_or_off(void) {
  char char_in_message_from_app = 0;
  uart2_getChar(&char_in_message_from_app, 0);

  if (('~' != char_in_message_from_app) && ('\0' != char_in_message_from_app)) {
    TX_buffer[bufferindex++] = char_in_message_from_app;
  } else {
    TX_buffer[bufferindex++] = '\0';
    bufferindex = 0;
  }

  if (!strcmp(ON, TX_buffer)) {
    turn_on_car();
    memset(TX_buffer, '\0', (sizeof(TX_buffer)));  // memset to clear the buffer
  } else if (!strcmp(OFF, TX_buffer)) {
    turn_off_car();
    memset(TX_buffer, '\0', (sizeof(TX_buffer)));
  }
}

bool turn_on_car(void) {
  on_off_cmd.BRIDGE_DATA_cmd = 1;
  on_off_msg_hdr = dbc_encode_BRIDGE_DATA(on_off_can_msg.data.bytes, &on_off_cmd);
  on_off_can_msg.msg_id = on_off_msg_hdr.mid;
  on_off_can_msg.frame_fields.data_len = on_off_msg_hdr.dlc;
  return CAN_tx(can1, &on_off_can_msg, 0);
}

bool turn_off_car(void) {
  on_off_cmd.BRIDGE_DATA_cmd = 0;
  on_off_msg_hdr = dbc_encode_BRIDGE_DATA(on_off_can_msg.data.bytes, &on_off_cmd);
  on_off_can_msg.msg_id = on_off_msg_hdr.mid;
  on_off_can_msg.frame_fields.data_len = on_off_msg_hdr.dlc;
  return CAN_tx(can1, &on_off_can_msg, 0);
}
