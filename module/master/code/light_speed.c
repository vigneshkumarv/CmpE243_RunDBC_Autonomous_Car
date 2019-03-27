#include "light_speed.h"
#include "generated_can/generated_can.h"
#include "stdio.h"
#include "wrappers\ls_wrapper.h"

can_msg_t rx_can_message;
static GEO_DATA_t geo_can_msg = {0};
static SENSOR_DATA_t sensor_can_msg = {0};
static BRIDGE_DATA_t bridge_can_msg = {0};
static MOTOR_DATA_t motor_can_msg = {0};

// The MIA functions require that you define the:
//   - Time when the handle_mia() functions will replace the data with the MIA
//   - The MIA data itself (ie: MOTOR_STATUS__MIA_MSG)
const uint32_t GEO_DATA__MIA_MS = 100;
const GEO_DATA_t GEO_DATA__MIA_MSG = { .GEO_DATA_cmd = 0 };
const uint32_t SENSOR_DATA__MIA_MS = 100;
const SENSOR_DATA_t SENSOR_DATA__MIA_MSG = {.SENSOR_DATA_cmd = 0};
const uint32_t BRIDGE_DATA__MIA_MS = 100;
const BRIDGE_DATA_t BRIDGE_DATA__MIA_MSG = {.BRIDGE_DATA_cmd = 0};
const uint32_t MOTOR_DATA__MIA_MS = 100;
const MOTOR_DATA_t MOTOR_DATA__MIA_MSG = {.MOTOR_DATA_cmd = 0};


void init_light_speed(void) {
  CAN_init(can1, 100, 64, 64, NULL, NULL);

  CAN_reset_bus(can1);
  CAN_bypass_filter_accept_all_msgs();
}

void check_and_restart_can() {
  if ((CAN_is_bus_off(can1))) {
    CAN_reset_bus(can1);
  }
}

void update_speed(light_speed_S* speeds) {

  while (CAN_rx(can1, &rx_can_message, 0)) {
    dbc_msg_hdr_t rx_msg_hdr;
    rx_msg_hdr.dlc = rx_can_message.frame_fields.data_len;
    rx_msg_hdr.mid = rx_can_message.msg_id;
    dbc_decode_GEO_DATA(&geo_can_msg, rx_can_message.data.bytes, &rx_msg_hdr);
    dbc_decode_SENSOR_DATA(&sensor_can_msg, rx_can_message.data.bytes, &rx_msg_hdr);
    dbc_decode_BRIDGE_DATA(&bridge_can_msg, rx_can_message.data.bytes, &rx_msg_hdr);
    dbc_decode_MOTOR_DATA(&motor_can_msg, rx_can_message.data.bytes, &rx_msg_hdr);
  }

  dbc_handle_mia_GEO_DATA(&geo_can_msg, 10);
  dbc_handle_mia_SENSOR_DATA(&sensor_can_msg, 10);
  dbc_handle_mia_BRIDGE_DATA(&bridge_can_msg, 10);
  dbc_handle_mia_MOTOR_DATA(&motor_can_msg, 10);

  speeds->GEO_light_percent = geo_can_msg.GEO_DATA_cmd;
  speeds->SENSOR_light_percent = sensor_can_msg.SENSOR_DATA_cmd;
  speeds->BRIDGE_light_percent = bridge_can_msg.BRIDGE_DATA_cmd;
  speeds->MOTOR_light_percent = motor_can_msg.MOTOR_DATA_cmd;

  speeds->average_speed_percent = (speeds->BRIDGE_light_percent + speeds->GEO_light_percent +
                                   speeds->MOTOR_light_percent + speeds->SENSOR_light_percent) /
                                  4;
}
void send_speed(uint8_t percent_speed) {
  MASTER_SPEED_t MASTER_speed = {0};
  MASTER_speed.MASTER_DATA_cmd = percent_speed;

  can_msg_t can_msg = {0};
  dbc_msg_hdr_t msg_hdr = dbc_encode_MASTER_SPEED(can_msg.data.bytes, &MASTER_speed);
  can_msg.msg_id = msg_hdr.mid;
  can_msg.frame_fields.data_len = msg_hdr.dlc;

  CAN_tx(can1, &can_msg, 0);
}
