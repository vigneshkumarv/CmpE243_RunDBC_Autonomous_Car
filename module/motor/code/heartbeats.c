// heartbeats.c (program is on the motor controller)
// handles heartbeat from motor to master
// handles heartbeat from master to motor

#include "heartbeats.h"
#include <can.h>
#include "LED_wrapper.h"
#include "generated-can/generated_can.h"
//#include "motor_drive.h"

// XXX Do you need all these headers?
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

MASTER_HEARTBEAT_t rx_master_heartbeat_msg;
const uint32_t MASTER_HEARTBEAT__MIA_MS = 3000;
const MASTER_HEARTBEAT_t MASTER_HEARTBEAT__MIA_MSG = {.MASTER_HEARTBEAT_cmd = 1};

void handle_heartbeats(void) {
  // send heartbeat to master
  // XXX This probably should be global, othewrise you lose this data when functions exits
  // But wait... you are sending this out, so it does not need to be global
  MOTOR_HEARTBEAT_t motor_heartbeat = {0};
  motor_heartbeat.MOTOR_HEARTBEAT_cmd = 0;
  dbc_encode_and_send_MOTOR_HEARTBEAT(&motor_heartbeat);

  // receive heartbeat from master
  can_msg_t can_msg;
  // int val = 0;

  // Huge bug... you cannot eat messages for everyone else here
#if 0
  while (CAN_rx(can1, &can_msg, 0)) {
    dbc_msg_hdr_t can_msg_hdr;
    can_msg_hdr.mid = can_msg.msg_id;
    can_msg_hdr.dlc = can_msg.frame_fields.data_len;
    dbc_decode_MASTER_HEARTBEAT(&rx_master_heartbeat_msg, can_msg.data.bytes, &can_msg_hdr);
    // val = can_msg.data.qword;
  }
#endif

  // handle mia from master heartbeat
<<<<<<< module/motor/code/heartbeats.c
  // XXX: If you are expecting this function to be called at 1Hz
  // then this function should be named 'handle_heartbeat_1Hz()'
  if (dbc_handle_mia_MASTER_HEARTBEAT(&rx_master_heartbeat_msg, 1000)) {  // an mia has occurred, do something
    // printf("MIA from heartbeat!\n");
=======
  if (dbc_handle_mia_MASTER_HEARTBEAT(&rx_master_heartbeat_msg, 1000)) {  // an mia has occurred, do something
>>>>>>> module/motor/code/heartbeats.c
    LED_2_on();
    // Stop();

  } else {
    // LED_2_off();
  }
}
