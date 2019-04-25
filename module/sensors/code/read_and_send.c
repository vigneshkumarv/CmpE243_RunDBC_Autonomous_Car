#include "read_and_send.h"

//extern int get_distance_cm_middle_ultrasonic();

// this function reads all sensors
void read_left_right_ultrasonic_sensors(void) {
  distance_sensor_read(left);
  //delay_ms(10);
  distance_sensor_read(right);
}

void read_middle_rear_sensors(void) {
  distance_sensor_read(middle);
  // printf("middle distance: %d\n", get_distance_cm_middle_ultrasonic());
  distance_sensor_read(rear);
  // printf("rear distance: %d\n", get_distance_cm_rear_ir());
}

void read_left_right_bumper_sensors(void) {
  bumper_sensor_read(left);
  bumper_sensor_read(right);
}

void send_can_msg(can_t* sensor_module) {
  can_msg_t can_msg = {0};

  // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
  dbc_msg_hdr_t msg_hdr = dbc_encode_SENSOR_DATA(can_msg.data.bytes, &sensor_data);
  can_msg.msg_id = msg_hdr.mid;
  can_msg.frame_fields.data_len = msg_hdr.dlc;

  // Queue the CAN message to be sent out
  CAN_tx(*sensor_module, &can_msg, 0);
}

void send_heartbeat_msg(can_t* sensor_module) {
  SENSOR_HEARTBEAT_t heartbeat = {0};
  heartbeat.SENSOR_HEARTBEAT_cmd = 0;  // heartbeat msg data field is 0
  can_msg_t can_msg = {0};

  // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
  dbc_msg_hdr_t msg_hdr = dbc_encode_SENSOR_HEARTBEAT(can_msg.data.bytes, &heartbeat);
  can_msg.msg_id = msg_hdr.mid;
  can_msg.frame_fields.data_len = msg_hdr.dlc;

  // Queue the CAN message to be sent out
  CAN_tx(*sensor_module, &can_msg, 0);
}
