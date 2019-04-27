// master_can.c

/******************************************************************************
 *
 * STANDARD INCLUDES
 *
 ******************************************************************************/
#include <stdbool.h>
#include <stdio.h>

/******************************************************************************
 *
 * CUSTOM INCLUDES
 *
 ******************************************************************************/
#include "LED_wrapper.h"
#include "master_can.h"

/******************************************************************************
 *
 * CONSTANTS
 *
 ******************************************************************************/
// The MIA functions require that you define the:
//   - Time when the handle_mia() functions will replace the data with the MIA
//   - The MIA data itself (ie: MOTOR_STATUS__MIA_MSG)
const uint32_t GEO_HEARTBEAT__MIA_MS = 3000;
const GEO_HEARTBEAT_t GEO_HEARTBEAT__MIA_MSG = {.GEO_HEARTBEAT_cmd = 1};
const uint32_t SENSOR_HEARTBEAT__MIA_MS = 3000;
const SENSOR_HEARTBEAT_t SENSOR_HEARTBEAT__MIA_MSG = {.SENSOR_HEARTBEAT_cmd = 1};
const uint32_t BRIDGE_HEARTBEAT__MIA_MS = 3000;
const BRIDGE_HEARTBEAT_t BRIDGE_HEARTBEAT__MIA_MSG = {.BRIDGE_HEARTBEAT_cmd = 1};
const uint32_t MOTOR_HEARTBEAT__MIA_MS = 3000;
const MOTOR_HEARTBEAT_t MOTOR_HEARTBEAT__MIA_MSG = {.MOTOR_HEARTBEAT_cmd = 1};

const uint32_t SENSOR_DATA__MIA_MS = 3000;
const SENSOR_DATA_t SENSOR_DATA__MIA_MSG = {.SENSOR_DATA_LeftBumper = true,
                                            .SENSOR_DATA_RightBumper = true,
                                            .SENSOR_DATA_LeftUltrasonic = 0,
                                            .SENSOR_DATA_RightUltrasonic = 0,
                                            .SENSOR_DATA_MiddleUltrasonic = 0,
                                            .SENSOR_DATA_RearIr = 0};

/******************************************************************************
 *
 * GLOBAL VARIABLES
 *
 ******************************************************************************/
static GEO_HEARTBEAT_t geo_heartbeat_msg = {0};
static SENSOR_HEARTBEAT_t sensor_heartbeat_msg = {0};
static BRIDGE_HEARTBEAT_t bridge_heartbeat_msg = {0};
static MOTOR_HEARTBEAT_t motor_heartbeat_msg = {0};
static SENSOR_DATA_t sensor_data_msg = {0};

/******************************************************************************
 *
 * PUBLIC FUNCTIONS
 *
 ******************************************************************************/
bool init_can(void) {
  bool can_is_initialized = CAN_init(can1, 100, 64, 64, NULL, NULL);

  CAN_reset_bus(can1);
  CAN_bypass_filter_accept_all_msgs();

  return can_is_initialized;
}

void check_and_restart_can() {
  if ((CAN_is_bus_off(can1))) {
    CAN_reset_bus(can1);
  }
}

bool read_can_50Hz(navigation_sensors_S* sensor_values) {
  bool all_heartbeats_good = true;
  can_msg_t rx_msg = {0};
  while (CAN_rx(can1, &rx_msg, 0)) {
    dbc_msg_hdr_t rx_msg_hdr;
    rx_msg_hdr.dlc = rx_msg.frame_fields.data_len;
    rx_msg_hdr.mid = rx_msg.msg_id;
    dbc_decode_BRIDGE_HEARTBEAT(&bridge_heartbeat_msg, rx_msg.data.bytes, &rx_msg_hdr);
    dbc_decode_GEO_HEARTBEAT(&geo_heartbeat_msg, rx_msg.data.bytes, &rx_msg_hdr);
    dbc_decode_MOTOR_HEARTBEAT(&motor_heartbeat_msg, rx_msg.data.bytes, &rx_msg_hdr);
    dbc_decode_SENSOR_HEARTBEAT(&sensor_heartbeat_msg, rx_msg.data.bytes, &rx_msg_hdr);

    if (dbc_decode_SENSOR_DATA(&sensor_data_msg, rx_msg.data.bytes, &rx_msg_hdr)) {
      sensor_values->left_bumper_triggered = (bool)sensor_data_msg.SENSOR_DATA_LeftBumper;
      sensor_values->right_bumper_triggered = (bool)sensor_data_msg.SENSOR_DATA_RightBumper;
      sensor_values->left_ultrasonic_cm = sensor_data_msg.SENSOR_DATA_LeftUltrasonic;
      sensor_values->right_ultrasonic_cm = sensor_data_msg.SENSOR_DATA_RightUltrasonic;
      sensor_values->middle_ultrasonic_cm = sensor_data_msg.SENSOR_DATA_MiddleUltrasonic;
      sensor_values->rear_ir_cm = sensor_data_msg.SENSOR_DATA_RearIr;
    }
  }

  if (dbc_handle_mia_BRIDGE_HEARTBEAT(&bridge_heartbeat_msg, 20)) {
    LED_1_on();
    all_heartbeats_good = false;
  }
  if (dbc_handle_mia_GEO_HEARTBEAT(&geo_heartbeat_msg, 20)) {
    LED_2_on();
    all_heartbeats_good = false;
  }
  if (dbc_handle_mia_MOTOR_HEARTBEAT(&motor_heartbeat_msg, 20)) {
    LED_3_on();
    all_heartbeats_good = false;
  }
  if (dbc_handle_mia_SENSOR_HEARTBEAT(&sensor_heartbeat_msg, 20)) {
    LED_4_on();
    all_heartbeats_good = false;
  }
  if (dbc_handle_mia_SENSOR_DATA(&sensor_data_msg, 20)) {
    sensor_values->left_bumper_triggered = (bool)sensor_data_msg.SENSOR_DATA_LeftBumper;
    sensor_values->right_bumper_triggered = (bool)sensor_data_msg.SENSOR_DATA_RightBumper;
    sensor_values->left_ultrasonic_cm = sensor_data_msg.SENSOR_DATA_LeftUltrasonic;
    sensor_values->right_ultrasonic_cm = sensor_data_msg.SENSOR_DATA_RightUltrasonic;
    sensor_values->middle_ultrasonic_cm = sensor_data_msg.SENSOR_DATA_MiddleUltrasonic;
    sensor_values->rear_ir_cm = sensor_data_msg.SENSOR_DATA_RearIr;
  }

  if (0 == bridge_heartbeat_msg.BRIDGE_HEARTBEAT_cmd) {
    LED_1_off();
  }
  if (0 == geo_heartbeat_msg.GEO_HEARTBEAT_cmd) {
    LED_2_off();
  }
  if (0 == motor_heartbeat_msg.MOTOR_HEARTBEAT_cmd) {
    LED_3_off();
  }
  if (0 == sensor_heartbeat_msg.SENSOR_HEARTBEAT_cmd) {
    LED_4_off();
  }

  return all_heartbeats_good;
}

void send_drive_cmd(navigation_motor_cmd_S drive_data) {
  MASTER_DRIVE_CMD_t drive_msg = {0};
  drive_msg.MASTER_DRIVE_CMD_direction = drive_data.motor_direction;
  drive_msg.MASTER_DRIVE_CMD_speed = drive_data.motor_speed;
  drive_msg.MASTER_DRIVE_CMD_steer = drive_data.steer_direction;

  can_msg_t can_msg = {0};

  // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
  dbc_msg_hdr_t msg_hdr = dbc_encode_MASTER_DRIVE_CMD(can_msg.data.bytes, &drive_msg);
  can_msg.msg_id = msg_hdr.mid;
  can_msg.frame_fields.data_len = msg_hdr.dlc;

  // Queue the CAN message to be sent out
  CAN_tx(can1, &can_msg, 0);
}

void send_heartbeat_msg() {
  MASTER_HEARTBEAT_t heartbeat = {0};  // heartbeat msg data field is 0
  can_msg_t can_msg = {0};

  // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
  dbc_msg_hdr_t msg_hdr = dbc_encode_MASTER_HEARTBEAT(can_msg.data.bytes, &heartbeat);
  can_msg.msg_id = msg_hdr.mid;
  can_msg.frame_fields.data_len = msg_hdr.dlc;

  // Queue the CAN message to be sent out
  CAN_tx(can1, &can_msg, 0);
}
