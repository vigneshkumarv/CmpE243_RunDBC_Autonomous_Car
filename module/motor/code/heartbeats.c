// heartbeats.c (program is on the motor controller)
// handles heartbeat from motor to master
// handles heartbeat from master to motor

#include "heartbeats.h"
#include <can.h>
#include "LED_wrapper.h"
#include "generated-can/generated_can.h"
//#include "motor_drive.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

MASTER_HEARTBEAT_t rx_master_heartbeat_msg;
const uint32_t MASTER_HEARTBEAT__MIA_MS = 3000;
const MASTER_HEARTBEAT_t MASTER_HEARTBEAT__MIA_MSG = {.MASTER_HEARTBEAT_cmd = 1};

void handle_heartbeats(void) {
  // send heartbeat to master
  MOTOR_HEARTBEAT_t motor_heartbeat = {0};
  motor_heartbeat.MOTOR_HEARTBEAT_cmd = 0;
  dbc_encode_and_send_MOTOR_HEARTBEAT(&motor_heartbeat);

  // receive heartbeat from master
  can_msg_t can_msg;
  // int val = 0;
  while (CAN_rx(can1, &can_msg, 0)) {
    dbc_msg_hdr_t can_msg_hdr;
    can_msg_hdr.mid = can_msg.msg_id;
    can_msg_hdr.dlc = can_msg.frame_fields.data_len;
    dbc_decode_MASTER_HEARTBEAT(&rx_master_heartbeat_msg, can_msg.data.bytes, &can_msg_hdr);
    // val = can_msg.data.qword;
  }
  // handle mia from master heartbeat
  if (dbc_handle_mia_MASTER_HEARTBEAT(&rx_master_heartbeat_msg, 1000)) {  // an mia has occurred, do something
      //printf("MIA from heartbeat!\n");
      LED_2_on();
    // Stop();

  } else {
    // LED_2_off();
  }
}
