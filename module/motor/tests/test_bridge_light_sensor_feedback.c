#include <stdbool.h>
#include <stdint.h>
#include "C:\SJSU_Dev\projects\lpc1758_freertos\_can_dbc\generated_can.h"
#include "Mockcan.h"
#include "bridge_light_sensor_feedback.h"
#include "unity.h"

void test_Bridge_CAN_Init(void) {
  CAN_init_ExpectAndReturn(can1, 100, 64, 64, NULL, NULL, true);
  CAN_reset_bus_Expect(can1);
  Bridge_CAN_Init();
}

void test_Bridge_CAN_Transmit(void) {
  CAN_tx_ExpectAndReturn(can1, NULL, 0, true);
  CAN_tx_IgnoreArg_msg();
  Bridge_CAN_Transmit();

  /*
  BRIDGE_DATA_t bridge_message = { 0 };
  bridge_message.BRIDGE_DATA_cmd = 10;
  CAN_tx_ExpectAndReturn(can1, &bridge_message, 0, true);
  */
}

void test_Bridge_CAN_Check(void) {
  CAN_is_bus_off_ExpectAndReturn(can1, true);
  CAN_reset_bus_Expect(can1);
  Bridge_CAN_Check();
}
