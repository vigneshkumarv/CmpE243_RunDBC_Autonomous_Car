/*
 * bridge_can.c
 *
 *  Created on: Apr 26, 2019
 *      Author: Vignesh
 */

#include "bridge_can.h"
#include "path_finding.h"
#include "uart0_min.h"
#include "uart_wrapper.h"

#define SIZE 100
#define ON "CARON"
#define OFF "CAROFF"

can_msg_t can_msg = {0};
GEO_DATA_t geo_distance_and_angle_data = {0};
BRIDGE_DATA_t on_off_cmd = {0};
SENSOR_DATA_t sensor_data = {0};
Geo_Data_S geo_to_android = {0};
Sensor_Data_S sensor_to_android = {0};
dbc_msg_hdr_t can_msg_hdr, on_off_msg_hdr;

char TX_buffer[SIZE] = {0};
char RX_buffer[SIZE] = {0};
char Location_buffer[SIZE] = {0};
static int bufferindex = 0;

bool bridge_uart2_init(void) { return uart2_init(9600, 100, 64); }

bool bridge_CAN_init(void) {
  CAN_init(can1, 100, 100, 32, NULL, NULL);
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
  while (CAN_rx(can1, &can_msg, 0)) {
    can_msg_hdr.dlc = can_msg.frame_fields.data_len;
    can_msg_hdr.mid = can_msg.msg_id;
    receive_parameters(&geo_to_android, &sensor_to_android);
  }
}

void receive_parameters(Geo_Data_S *geo_data, Sensor_Data_S *sensor_data_to_android) {
  if (dbc_decode_GEO_DATA(&geo_distance_and_angle_data, can_msg.data.bytes, &can_msg_hdr)) {
    geo_data->deflection_angle = geo_distance_and_angle_data.GEO_DATA_Angle;
    geo_data->distance_from_destination = geo_distance_and_angle_data.GEO_DATA_Distance;
  }

  if (dbc_decode_GEO_COORDINATE_DATA(&geo_source_data, can_msg.data.bytes, &can_msg_hdr)) {
    geo_data->geo_src_latitude = geo_source_data.GEO_DATA_Latitude;
    geo_data->geo_src_longitude = geo_source_data.GEO_DATA_Longitude;
    current_location_set(geo_source_data.GEO_DATA_Longitude, geo_source_data.GEO_DATA_Latitude);
  }

  if (dbc_decode_SENSOR_DATA(&sensor_data, can_msg.data.bytes, &can_msg_hdr)) {
    sensor_data_to_android->LeftUltrasonic = sensor_data.SENSOR_DATA_LeftUltrasonic;
    sensor_data_to_android->RightUltrasonic = sensor_data.SENSOR_DATA_RightUltrasonic;
    sensor_data_to_android->MiddleUltrasonic = sensor_data.SENSOR_DATA_MiddleUltrasonic;
    sensor_data_to_android->RearIr = sensor_data.SENSOR_DATA_RearIr;
  }
}

void compile_and_send_data(void) {
  snprintf(RX_buffer, sizeof(RX_buffer), "~A%.2fD%0.2fS%iR%iM%iI%iL%fG%f#", geo_to_android.deflection_angle,
           geo_to_android.distance_from_destination, sensor_to_android.LeftUltrasonic,
           sensor_to_android.RightUltrasonic, sensor_to_android.MiddleUltrasonic, sensor_to_android.RearIr,
           geo_to_android.geo_src_latitude, geo_to_android.geo_src_longitude);
  uart2_putLine(RX_buffer, 0);
}

void bridge_send_start_stop_CAN_10Hz(void) { get_data_from_app(); }

void get_data_from_app(void) {
  char char_in_message_from_app = 0;
  uart2_getChar(&char_in_message_from_app, 0);

  // xxx: buffer overflow issues
  if (('#' != char_in_message_from_app) && ('\0' != char_in_message_from_app)) {
    TX_buffer[bufferindex++] = char_in_message_from_app;
    // printf("%c\n",char_in_message_from_app); working
  } else {
    TX_buffer[bufferindex] = '\0';
    bufferindex = 0;
    if (TX_buffer != '\0') {
      // printf("%s",TX_buffer); printing data :)
      parse_received_data(TX_buffer, sizeof(TX_buffer));
    }
  }
}

// xxx: You should only do this when you have a complete sentence
// which happens when you get the NULL char above
void parse_received_data(char *TX, size_t size_of_tx) {
  int count = 0;
  float dest_lat = 0, dest_lon = 0;
  char *ptr = strtok(TX, "~$");
  char *start_stop = NULL;
  while (ptr != NULL) {
    if (count == 0) {
      start_stop = ptr;
    }
    if (count == 1) {
      dest_lat = atof(ptr);
    }
    if (count == 2) {
      dest_lon = atof(ptr);
    }
    ptr = strtok(NULL, "$");
    count++;
  }
  count = 0;
  if(dest_lat != 0.0 && dest_lon != 0.0)
  {
      printf("dest_long and lat: %f, %f   ", dest_lon, dest_lat);
  }
  // if the destination has not been set and we are getting destination coordinates and the car command is CAR_ON
  if(destination.latitude <= 0.0 && destination.longitude >= 0.0 && dest_lat != 0.0 && dest_lon != 0.0 && start_stop[4] == 'N')
  {
      printf("dest_long and lat set   ");
      destination_set(dest_lon, dest_lat);
  }
  if (!strcmp(ON, start_stop)) {
    turn_on_car();
  } else if (!strcmp(OFF, start_stop)) {
    turn_off_car();
  }
  memset(TX_buffer, '\0', size_of_tx);
}

bool turn_on_car(void) {
  can_msg_t on_off_can_msg;
  on_off_cmd.BRIDGE_DATA_cmd = 1;
  on_off_msg_hdr = dbc_encode_BRIDGE_DATA(on_off_can_msg.data.bytes, &on_off_cmd);
  on_off_can_msg.msg_id = on_off_msg_hdr.mid;
  on_off_can_msg.frame_fields.data_len = on_off_msg_hdr.dlc;
  return CAN_tx(can1, &on_off_can_msg, 0);
}

bool turn_off_car(void) {
  can_msg_t on_off_can_msg;
  on_off_cmd.BRIDGE_DATA_cmd = 0;
  on_off_msg_hdr = dbc_encode_BRIDGE_DATA(on_off_can_msg.data.bytes, &on_off_cmd);
  on_off_can_msg.msg_id = on_off_msg_hdr.mid;
  on_off_can_msg.frame_fields.data_len = on_off_msg_hdr.dlc;
  return CAN_tx(can1, &on_off_can_msg, 0);
}
