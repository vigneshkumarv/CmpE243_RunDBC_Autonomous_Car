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

/******************************************************************************
 *
 * GLOBAL VARIABLES
 *
 ******************************************************************************/
static GEO_HEARTBEAT_t geo_heartbeat_msg = {0};
static SENSOR_HEARTBEAT_t sensor_heartbeat_msg = {0};
static BRIDGE_HEARTBEAT_t bridge_heartbeat_msg = {0};
static MOTOR_HEARTBEAT_t motor_heartbeat_msg = {0};

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

bool read_can(void) {
  bool all_heartbeats_good = true;
  can_msg_t heartbeat_rx_msg = {0};
  while (CAN_rx(can1, &heartbeat_rx_msg, 0)) {
    dbc_msg_hdr_t rx_msg_hdr;
    rx_msg_hdr.dlc = heartbeat_rx_msg.frame_fields.data_len;
    rx_msg_hdr.mid = heartbeat_rx_msg.msg_id;
    dbc_decode_BRIDGE_HEARTBEAT(&bridge_heartbeat_msg, heartbeat_rx_msg.data.bytes, &rx_msg_hdr);
    dbc_decode_GEO_HEARTBEAT(&geo_heartbeat_msg, heartbeat_rx_msg.data.bytes, &rx_msg_hdr);
    dbc_decode_MOTOR_HEARTBEAT(&motor_heartbeat_msg, heartbeat_rx_msg.data.bytes, &rx_msg_hdr);
    dbc_decode_SENSOR_HEARTBEAT(&sensor_heartbeat_msg, heartbeat_rx_msg.data.bytes, &rx_msg_hdr);
  }

  if (dbc_handle_mia_BRIDGE_HEARTBEAT(&bridge_heartbeat_msg, 100)) {
    LED_1_on();
    all_heartbeats_good = false;
  }
  if (dbc_handle_mia_GEO_HEARTBEAT(&geo_heartbeat_msg, 100)) {
    LED_2_on();
    all_heartbeats_good = false;
  }
  if (dbc_handle_mia_MOTOR_HEARTBEAT(&motor_heartbeat_msg, 100)) {
    LED_3_on();
    all_heartbeats_good = false;
  }
  if (dbc_handle_mia_SENSOR_HEARTBEAT(&sensor_heartbeat_msg, 100)) {
    LED_4_on();
    all_heartbeats_good = false;
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

void send_drive_cmd(MASTER_DRIVE_CMD_t* drive_data) {
  can_msg_t can_msg = {0};

  // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
  dbc_msg_hdr_t msg_hdr = dbc_encode_MASTER_DRIVE_CMD(can_msg.data.bytes, drive_data);
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
