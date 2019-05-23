/// DBC file: ../../../../autonomous-car/shared_code/_can_dbc/243.dbc    Self node: 'MASTER'  (ALL = 0)
/// This file can be included by a source file, for example: #include "generated.h"
#ifndef __GENERATED_DBC_PARSER
#define __GENERATED_DBC_PARSER
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/// Extern function needed for dbc_encode_and_send()
extern bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]);

/// Missing in Action structure
typedef struct {
  uint32_t is_mia : 1;           ///< Missing in action flag
  uint32_t mia_counter_ms : 31;  ///< Missing in action counter
} dbc_mia_info_t;

/// CAN message header structure
typedef struct {
  uint32_t mid;  ///< Message ID of the message
  uint8_t dlc;   ///< Data length of the message
} dbc_msg_hdr_t;

static const dbc_msg_hdr_t GEO_HEARTBEAT_HDR = {768, 1};
static const dbc_msg_hdr_t SENSOR_HEARTBEAT_HDR = {256, 1};
static const dbc_msg_hdr_t BRIDGE_HEARTBEAT_HDR = {1024, 1};
static const dbc_msg_hdr_t MOTOR_HEARTBEAT_HDR = {512, 1};
static const dbc_msg_hdr_t MASTER_HEARTBEAT_HDR = {0, 1};
static const dbc_msg_hdr_t GEO_COORDINATE_DATA_HDR = {770, 8};
static const dbc_msg_hdr_t GEO_DATA_HDR = {769, 8};
static const dbc_msg_hdr_t GEO_DEBUG_DATA_HDR = {771, 8};
static const dbc_msg_hdr_t SENSOR_DATA_HDR = {257, 8};
static const dbc_msg_hdr_t BRIDGE_DATA_CMD_HDR = {1025, 1};
static const dbc_msg_hdr_t BRIDGE_CHECKPOINT_HDR = {1026, 8};
static const dbc_msg_hdr_t MOTOR_DATA_HDR = {513, 4};
static const dbc_msg_hdr_t MOTOR_DEBUG_RPM_PARTIAL_HDR = {514, 4};
static const dbc_msg_hdr_t MOTOR_DEBUG_RPM_ACTUAL_HDR = {515, 4};
static const dbc_msg_hdr_t MOTOR_DEBUG_PI_ERROR_HDR = {516, 4};
static const dbc_msg_hdr_t MOTOR_DEBUG_LARGE_ERROR_CNT_HDR = {517, 4};
static const dbc_msg_hdr_t MOTOR_DEBUG_PROPORTIONAL_CMD_HDR = {518, 4};
static const dbc_msg_hdr_t MOTOR_DEBUG_INTEGRAL_CMD_HDR = {519, 4};
static const dbc_msg_hdr_t MOTOR_DEBUG_INTEGRAL_CMD_OLD_HDR = {520, 4};
static const dbc_msg_hdr_t MOTOR_DEBUG_OUTPUT_HDR = {521, 4};
static const dbc_msg_hdr_t MOTOR_DEBUG_PWM_ACTUAL_HDR = {522, 4};
static const dbc_msg_hdr_t MASTER_DRIVE_CMD_HDR = {1, 4};
static const dbc_msg_hdr_t MASTER_DEBUG_HDR = {2, 4};

/// Enumeration(s) for Message: 'MOTOR_DATA' from 'MOTOR'
typedef enum {
  stop_act = 0,
  forward_act = 1,
  backward_act = 2,
} MOTOR_DATA_direction_E;

/// Enumeration(s) for Message: 'MASTER_DRIVE_CMD' from 'MASTER'
typedef enum {
  stop_cmd = 0,
  forward_cmd = 1,
  backward_cmd = 2,
} MASTER_DRIVE_CMD_direction_E;

/// Enumeration(s) for Message: 'MASTER_DEBUG' from 'MASTER'
typedef enum {
  NAV_INIT = 0,
  NAV_WAIT = 1,
  NAV_NAVIGATE = 2,
  NAV_OBSTACLE_RIGHT = 3,
  NAV_OBSTACLE_LEFT = 4,
  NAV_OBSTACLE_MIDDLE_FAR = 5,
  NAV_OBSTACLE_MIDDLE_CLOSE = 6,
} MASTER_DEBUG_navigation_state_enum_E;

/// Message: GEO_HEARTBEAT from 'GEO', DLC: 1 byte(s), MID: 768
typedef struct {
  uint8_t GEO_HEARTBEAT_cmd;  ///< B7:0   Destination: MASTER

  dbc_mia_info_t mia_info;
} GEO_HEARTBEAT_t;

/// Message: SENSOR_HEARTBEAT from 'SENSOR', DLC: 1 byte(s), MID: 256
typedef struct {
  uint8_t SENSOR_HEARTBEAT_cmd;  ///< B7:0   Destination: MASTER

  dbc_mia_info_t mia_info;
} SENSOR_HEARTBEAT_t;

/// Message: BRIDGE_HEARTBEAT from 'BRIDGE', DLC: 1 byte(s), MID: 1024
typedef struct {
  uint8_t BRIDGE_HEARTBEAT_cmd;  ///< B7:0   Destination: MASTER

  dbc_mia_info_t mia_info;
} BRIDGE_HEARTBEAT_t;

/// Message: MOTOR_HEARTBEAT from 'MOTOR', DLC: 1 byte(s), MID: 512
typedef struct {
  uint8_t MOTOR_HEARTBEAT_cmd;  ///< B7:0   Destination: MASTER

  dbc_mia_info_t mia_info;
} MOTOR_HEARTBEAT_t;

/// Message: MASTER_HEARTBEAT from 'MASTER', DLC: 1 byte(s), MID: 0
typedef struct {
  uint8_t MASTER_HEARTBEAT_cmd;  ///< B7:0   Destination: MOTOR

  // No dbc_mia_info_t for a message that we will send
} MASTER_HEARTBEAT_t;

/// Message: GEO_COORDINATE_DATA from 'GEO', DLC: 8 byte(s), MID: 770
typedef struct {
  float GEO_DATA_Latitude;   ///< B31:0   Destination: MASTER,
  float GEO_DATA_Longitude;  ///< B63:32   Destination: MASTER,

  dbc_mia_info_t mia_info;
} GEO_COORDINATE_DATA_t;

/// Message: GEO_DATA from 'GEO', DLC: 8 byte(s), MID: 769
typedef struct {
  float GEO_DATA_Distance;  ///< B31:0   Destination: MASTER,BRIDGE
  float GEO_DATA_Angle;     ///< B63:32   Destination: MASTER,BRIDGE

  dbc_mia_info_t mia_info;
} GEO_DATA_t;

/// Message: GEO_DEBUG_DATA from 'GEO', DLC: 8 byte(s), MID: 771
typedef struct {
  uint8_t GEO_COMPASS_Calibration;  ///< B7:0   Destination: MASTER,BRIDGE
  float GEO_COMPASS_Heading;        ///< B39:8   Destination: MASTER,BRIDGE

  dbc_mia_info_t mia_info;
} GEO_DEBUG_DATA_t;

/// Message: SENSOR_DATA from 'SENSOR', DLC: 8 byte(s), MID: 257
typedef struct {
  uint8_t SENSOR_DATA_LeftBumper : 1;     ///< B0:0   Destination: MASTER
  uint8_t SENSOR_DATA_RightBumper : 1;    ///< B1:1   Destination: MASTER
  uint8_t SENSOR_DATA_LeftUltrasonic;     ///< B15:8   Destination: MASTER
  uint8_t SENSOR_DATA_RightUltrasonic;    ///< B23:16   Destination: MASTER
  uint16_t SENSOR_DATA_MiddleUltrasonic;  ///< B39:24   Destination: MASTER
  uint16_t SENSOR_DATA_RearIr;            ///< B55:40   Destination: MASTER

  dbc_mia_info_t mia_info;
} SENSOR_DATA_t;

/// Message: BRIDGE_DATA_CMD from 'BRIDGE', DLC: 1 byte(s), MID: 1025
typedef struct {
  uint8_t BRIDGE_DATA_CMD_start_stop : 1;  ///< B0:0  Min: 0 Max: 1   Destination: MASTER

  dbc_mia_info_t mia_info;
} BRIDGE_DATA_CMD_t;

/// Message: BRIDGE_CHECKPOINT from 'BRIDGE', DLC: 8 byte(s), MID: 1026
typedef struct {
  float BRIDGE_DATA_Latitude;   ///< B31:0   Destination: MASTER,GEO
  float BRIDGE_DATA_Longitude;  ///< B63:32   Destination: MASTER,GEO

  dbc_mia_info_t mia_info;
} BRIDGE_CHECKPOINT_t;

/// Message: MOTOR_DATA from 'MOTOR', DLC: 4 byte(s), MID: 513
typedef struct {
  int16_t MOTOR_DATA_steer;                         ///< B7:0   Destination: MASTER,BRIDGE
  float MOTOR_DATA_speed;                           ///< B23:8   Destination: MASTER,BRIDGE
  MOTOR_DATA_direction_E MOTOR_DATA_direction : 2;  ///< B25:24   Destination: MASTER,BRIDGE

  dbc_mia_info_t mia_info;
} MOTOR_DATA_t;

/// Message: MOTOR_DEBUG_RPM_PARTIAL from 'MOTOR', DLC: 4 byte(s), MID: 514
typedef struct {
  int32_t MOTOR_DEBUG_rpm_part;  ///< B31:0   Destination: MASTER,BRIDGE,DEBUG

  dbc_mia_info_t mia_info;
} MOTOR_DEBUG_RPM_PARTIAL_t;

/// Message: MOTOR_DEBUG_RPM_ACTUAL from 'MOTOR', DLC: 4 byte(s), MID: 515
typedef struct {
  float MOTOR_DEBUG_rpm_act;  ///< B31:0   Destination: MASTER,BRIDGE,DEBUG

  dbc_mia_info_t mia_info;
} MOTOR_DEBUG_RPM_ACTUAL_t;

/// Message: MOTOR_DEBUG_PI_ERROR from 'MOTOR', DLC: 4 byte(s), MID: 516
typedef struct {
  float MOTOR_DEBUG_pi_err;  ///< B31:0   Destination: MASTER,BRIDGE,DEBUG

  dbc_mia_info_t mia_info;
} MOTOR_DEBUG_PI_ERROR_t;

/// Message: MOTOR_DEBUG_LARGE_ERROR_CNT from 'MOTOR', DLC: 4 byte(s), MID: 517
typedef struct {
  uint32_t MOTOR_DEBUG_lg_err_cnt;  ///< B31:0   Destination: MASTER,BRIDGE,DEBUG

  dbc_mia_info_t mia_info;
} MOTOR_DEBUG_LARGE_ERROR_CNT_t;

/// Message: MOTOR_DEBUG_PROPORTIONAL_CMD from 'MOTOR', DLC: 4 byte(s), MID: 518
typedef struct {
  float MOTOR_DEBUG_prop_cmd;  ///< B31:0   Destination: MASTER,BRIDGE,DEBUG

  dbc_mia_info_t mia_info;
} MOTOR_DEBUG_PROPORTIONAL_CMD_t;

/// Message: MOTOR_DEBUG_INTEGRAL_CMD from 'MOTOR', DLC: 4 byte(s), MID: 519
typedef struct {
  float MOTOR_DEBUG_int_cmd;  ///< B31:0   Destination: MASTER,BRIDGE,DEBUG

  dbc_mia_info_t mia_info;
} MOTOR_DEBUG_INTEGRAL_CMD_t;

/// Message: MOTOR_DEBUG_INTEGRAL_CMD_OLD from 'MOTOR', DLC: 4 byte(s), MID: 520
typedef struct {
  float MOTOR_DEBUG_int_cmd_old;  ///< B31:0   Destination: MASTER,BRIDGE,DEBUG

  dbc_mia_info_t mia_info;
} MOTOR_DEBUG_INTEGRAL_CMD_OLD_t;

/// Message: MOTOR_DEBUG_OUTPUT from 'MOTOR', DLC: 4 byte(s), MID: 521
typedef struct {
  float MOTOR_DEBUG_out;  ///< B31:0   Destination: MASTER,BRIDGE,DEBUG

  dbc_mia_info_t mia_info;
} MOTOR_DEBUG_OUTPUT_t;

/// Message: MOTOR_DEBUG_PWM_ACTUAL from 'MOTOR', DLC: 4 byte(s), MID: 522
typedef struct {
  float MOTOR_DEBUG_pwm_act;  ///< B31:0   Destination: MASTER,BRIDGE,DEBUG

  dbc_mia_info_t mia_info;
} MOTOR_DEBUG_PWM_ACTUAL_t;

/// Message: MASTER_DRIVE_CMD from 'MASTER', DLC: 4 byte(s), MID: 1
typedef struct {
  int16_t MASTER_DRIVE_CMD_steer;                               ///< B7:0   Destination: MOTOR
  float MASTER_DRIVE_CMD_speed;                                 ///< B23:8   Destination: MOTOR
  MASTER_DRIVE_CMD_direction_E MASTER_DRIVE_CMD_direction : 2;  ///< B25:24   Destination: MOTOR

  // No dbc_mia_info_t for a message that we will send
} MASTER_DRIVE_CMD_t;

/// Message: MASTER_DEBUG from 'MASTER', DLC: 4 byte(s), MID: 2
typedef struct {
  MASTER_DEBUG_navigation_state_enum_E MASTER_DEBUG_navigation_state_enum;  ///< B7:0   Destination: MOTOR
  uint8_t MASTER_DEBUG_navigation_go : 1;                                   ///< B8:8   Destination: MOTOR

  // No dbc_mia_info_t for a message that we will send
} MASTER_DEBUG_t;

/// @{ These 'externs' need to be defined in a source file of your project
extern const uint32_t GEO_HEARTBEAT__MIA_MS;
extern const GEO_HEARTBEAT_t GEO_HEARTBEAT__MIA_MSG;
extern const uint32_t SENSOR_HEARTBEAT__MIA_MS;
extern const SENSOR_HEARTBEAT_t SENSOR_HEARTBEAT__MIA_MSG;
extern const uint32_t BRIDGE_HEARTBEAT__MIA_MS;
extern const BRIDGE_HEARTBEAT_t BRIDGE_HEARTBEAT__MIA_MSG;
extern const uint32_t MOTOR_HEARTBEAT__MIA_MS;
extern const MOTOR_HEARTBEAT_t MOTOR_HEARTBEAT__MIA_MSG;
extern const uint32_t GEO_COORDINATE_DATA__MIA_MS;
extern const GEO_COORDINATE_DATA_t GEO_COORDINATE_DATA__MIA_MSG;
extern const uint32_t GEO_DATA__MIA_MS;
extern const GEO_DATA_t GEO_DATA__MIA_MSG;
extern const uint32_t GEO_DEBUG_DATA__MIA_MS;
extern const GEO_DEBUG_DATA_t GEO_DEBUG_DATA__MIA_MSG;
extern const uint32_t SENSOR_DATA__MIA_MS;
extern const SENSOR_DATA_t SENSOR_DATA__MIA_MSG;
extern const uint32_t BRIDGE_DATA_CMD__MIA_MS;
extern const BRIDGE_DATA_CMD_t BRIDGE_DATA_CMD__MIA_MSG;
extern const uint32_t BRIDGE_CHECKPOINT__MIA_MS;
extern const BRIDGE_CHECKPOINT_t BRIDGE_CHECKPOINT__MIA_MSG;
extern const uint32_t MOTOR_DATA__MIA_MS;
extern const MOTOR_DATA_t MOTOR_DATA__MIA_MSG;
extern const uint32_t MOTOR_DEBUG_RPM_PARTIAL__MIA_MS;
extern const MOTOR_DEBUG_RPM_PARTIAL_t MOTOR_DEBUG_RPM_PARTIAL__MIA_MSG;
extern const uint32_t MOTOR_DEBUG_RPM_ACTUAL__MIA_MS;
extern const MOTOR_DEBUG_RPM_ACTUAL_t MOTOR_DEBUG_RPM_ACTUAL__MIA_MSG;
extern const uint32_t MOTOR_DEBUG_PI_ERROR__MIA_MS;
extern const MOTOR_DEBUG_PI_ERROR_t MOTOR_DEBUG_PI_ERROR__MIA_MSG;
extern const uint32_t MOTOR_DEBUG_LARGE_ERROR_CNT__MIA_MS;
extern const MOTOR_DEBUG_LARGE_ERROR_CNT_t MOTOR_DEBUG_LARGE_ERROR_CNT__MIA_MSG;
extern const uint32_t MOTOR_DEBUG_PROPORTIONAL_CMD__MIA_MS;
extern const MOTOR_DEBUG_PROPORTIONAL_CMD_t MOTOR_DEBUG_PROPORTIONAL_CMD__MIA_MSG;
extern const uint32_t MOTOR_DEBUG_INTEGRAL_CMD__MIA_MS;
extern const MOTOR_DEBUG_INTEGRAL_CMD_t MOTOR_DEBUG_INTEGRAL_CMD__MIA_MSG;
extern const uint32_t MOTOR_DEBUG_INTEGRAL_CMD_OLD__MIA_MS;
extern const MOTOR_DEBUG_INTEGRAL_CMD_OLD_t MOTOR_DEBUG_INTEGRAL_CMD_OLD__MIA_MSG;
extern const uint32_t MOTOR_DEBUG_OUTPUT__MIA_MS;
extern const MOTOR_DEBUG_OUTPUT_t MOTOR_DEBUG_OUTPUT__MIA_MSG;
extern const uint32_t MOTOR_DEBUG_PWM_ACTUAL__MIA_MS;
extern const MOTOR_DEBUG_PWM_ACTUAL_t MOTOR_DEBUG_PWM_ACTUAL__MIA_MSG;
/// @}

/// Not generating code for dbc_encode_GEO_HEARTBEAT() since the sender is GEO and we are MASTER

/// Not generating code for dbc_encode_SENSOR_HEARTBEAT() since the sender is SENSOR and we are MASTER

/// Not generating code for dbc_encode_BRIDGE_HEARTBEAT() since the sender is BRIDGE and we are MASTER

/// Not generating code for dbc_encode_MOTOR_HEARTBEAT() since the sender is MOTOR and we are MASTER

/// Encode MASTER's 'MASTER_HEARTBEAT' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_MASTER_HEARTBEAT(uint8_t bytes[8], MASTER_HEARTBEAT_t *from) {
  uint32_t raw;
  bytes[0] = bytes[1] = bytes[2] = bytes[3] = bytes[4] = bytes[5] = bytes[6] = bytes[7] = 0;

  raw = ((uint32_t)(((from->MASTER_HEARTBEAT_cmd)))) & 0xff;
  bytes[0] |= (((uint8_t)(raw)&0xff));  ///< 8 bit(s) starting from B0

  return MASTER_HEARTBEAT_HDR;
}

/// Encode and send for dbc_encode_MASTER_HEARTBEAT() message
static inline bool dbc_encode_and_send_MASTER_HEARTBEAT(MASTER_HEARTBEAT_t *from) {
  uint8_t bytes[8];
  const dbc_msg_hdr_t hdr = dbc_encode_MASTER_HEARTBEAT(bytes, from);
  return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}

/// Not generating code for dbc_encode_GEO_COORDINATE_DATA() since the sender is GEO and we are MASTER

/// Not generating code for dbc_encode_GEO_DATA() since the sender is GEO and we are MASTER

/// Not generating code for dbc_encode_GEO_DEBUG_DATA() since the sender is GEO and we are MASTER

/// Not generating code for dbc_encode_SENSOR_DATA() since the sender is SENSOR and we are MASTER

/// Not generating code for dbc_encode_BRIDGE_DATA_CMD() since the sender is BRIDGE and we are MASTER

/// Not generating code for dbc_encode_BRIDGE_CHECKPOINT() since the sender is BRIDGE and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DATA() since the sender is MOTOR and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DEBUG_RPM_PARTIAL() since the sender is MOTOR and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DEBUG_RPM_ACTUAL() since the sender is MOTOR and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DEBUG_PI_ERROR() since the sender is MOTOR and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DEBUG_LARGE_ERROR_CNT() since the sender is MOTOR and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DEBUG_PROPORTIONAL_CMD() since the sender is MOTOR and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DEBUG_INTEGRAL_CMD() since the sender is MOTOR and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DEBUG_INTEGRAL_CMD_OLD() since the sender is MOTOR and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DEBUG_OUTPUT() since the sender is MOTOR and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DEBUG_PWM_ACTUAL() since the sender is MOTOR and we are MASTER

/// Encode MASTER's 'MASTER_DRIVE_CMD' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_MASTER_DRIVE_CMD(uint8_t bytes[8], MASTER_DRIVE_CMD_t *from) {
  uint32_t raw;
  bytes[0] = bytes[1] = bytes[2] = bytes[3] = bytes[4] = bytes[5] = bytes[6] = bytes[7] = 0;

  // Stuff a real signed number into the DBC 8-bit signal
  raw = ((uint32_t)(((from->MASTER_DRIVE_CMD_steer)))) & 0xff;
  bytes[0] |= (((uint8_t)(raw)&0xff));  ///< 8 bit(s) starting from B0

  raw = ((uint32_t)(((from->MASTER_DRIVE_CMD_speed) / 0.1) + 0.5)) & 0xffff;
  bytes[1] |= (((uint8_t)(raw)&0xff));         ///< 8 bit(s) starting from B8
  bytes[2] |= (((uint8_t)(raw >> 8) & 0xff));  ///< 8 bit(s) starting from B16

  raw = ((uint32_t)(((from->MASTER_DRIVE_CMD_direction)))) & 0x03;
  bytes[3] |= (((uint8_t)(raw)&0x03));  ///< 2 bit(s) starting from B24

  return MASTER_DRIVE_CMD_HDR;
}

/// Encode and send for dbc_encode_MASTER_DRIVE_CMD() message
static inline bool dbc_encode_and_send_MASTER_DRIVE_CMD(MASTER_DRIVE_CMD_t *from) {
  uint8_t bytes[8];
  const dbc_msg_hdr_t hdr = dbc_encode_MASTER_DRIVE_CMD(bytes, from);
  return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}

/// Encode MASTER's 'MASTER_DEBUG' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_MASTER_DEBUG(uint8_t bytes[8], MASTER_DEBUG_t *from) {
  uint32_t raw;
  bytes[0] = bytes[1] = bytes[2] = bytes[3] = bytes[4] = bytes[5] = bytes[6] = bytes[7] = 0;

  raw = ((uint32_t)(((from->MASTER_DEBUG_navigation_state_enum)))) & 0xff;
  bytes[0] |= (((uint8_t)(raw)&0xff));  ///< 8 bit(s) starting from B0

  raw = ((uint32_t)(((from->MASTER_DEBUG_navigation_go)))) & 0x01;
  bytes[1] |= (((uint8_t)(raw)&0x01));  ///< 1 bit(s) starting from B8

  return MASTER_DEBUG_HDR;
}

/// Encode and send for dbc_encode_MASTER_DEBUG() message
static inline bool dbc_encode_and_send_MASTER_DEBUG(MASTER_DEBUG_t *from) {
  uint8_t bytes[8];
  const dbc_msg_hdr_t hdr = dbc_encode_MASTER_DEBUG(bytes, from);
  return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}

/// Decode GEO's 'GEO_HEARTBEAT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_GEO_HEARTBEAT(GEO_HEARTBEAT_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != GEO_HEARTBEAT_HDR.dlc || hdr->mid != GEO_HEARTBEAT_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));  ///< 8 bit(s) from B0
  to->GEO_HEARTBEAT_cmd = ((raw));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode SENSOR's 'SENSOR_HEARTBEAT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_SENSOR_HEARTBEAT(SENSOR_HEARTBEAT_t *to, const uint8_t bytes[8],
                                               const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != SENSOR_HEARTBEAT_HDR.dlc || hdr->mid != SENSOR_HEARTBEAT_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));  ///< 8 bit(s) from B0
  to->SENSOR_HEARTBEAT_cmd = ((raw));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode BRIDGE's 'BRIDGE_HEARTBEAT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_BRIDGE_HEARTBEAT(BRIDGE_HEARTBEAT_t *to, const uint8_t bytes[8],
                                               const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != BRIDGE_HEARTBEAT_HDR.dlc || hdr->mid != BRIDGE_HEARTBEAT_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));  ///< 8 bit(s) from B0
  to->BRIDGE_HEARTBEAT_cmd = ((raw));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_HEARTBEAT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_HEARTBEAT(MOTOR_HEARTBEAT_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != MOTOR_HEARTBEAT_HDR.dlc || hdr->mid != MOTOR_HEARTBEAT_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));  ///< 8 bit(s) from B0
  to->MOTOR_HEARTBEAT_cmd = ((raw));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Not generating code for dbc_decode_MASTER_HEARTBEAT() since 'MASTER' is not the recipient of any of the signals

/// Decode GEO's 'GEO_COORDINATE_DATA' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_GEO_COORDINATE_DATA(GEO_COORDINATE_DATA_t *to, const uint8_t bytes[8],
                                                  const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != GEO_COORDINATE_DATA_HDR.dlc || hdr->mid != GEO_COORDINATE_DATA_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  to->GEO_DATA_Latitude = ((raw * 1e-08));
  raw = ((uint32_t)((bytes[4])));         ///< 8 bit(s) from B32
  raw |= ((uint32_t)((bytes[5]))) << 8;   ///< 8 bit(s) from B40
  raw |= ((uint32_t)((bytes[6]))) << 16;  ///< 8 bit(s) from B48
  raw |= ((uint32_t)((bytes[7]))) << 24;  ///< 8 bit(s) from B56
  to->GEO_DATA_Longitude = ((raw * 1e-07) + (-150));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode GEO's 'GEO_DATA' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_GEO_DATA(GEO_DATA_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != GEO_DATA_HDR.dlc || hdr->mid != GEO_DATA_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  to->GEO_DATA_Distance = ((raw * 0.01));
  raw = ((uint32_t)((bytes[4])));         ///< 8 bit(s) from B32
  raw |= ((uint32_t)((bytes[5]))) << 8;   ///< 8 bit(s) from B40
  raw |= ((uint32_t)((bytes[6]))) << 16;  ///< 8 bit(s) from B48
  raw |= ((uint32_t)((bytes[7]))) << 24;  ///< 8 bit(s) from B56
  to->GEO_DATA_Angle = ((raw * 0.1) + (-180));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode GEO's 'GEO_DEBUG_DATA' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_GEO_DEBUG_DATA(GEO_DEBUG_DATA_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != GEO_DEBUG_DATA_HDR.dlc || hdr->mid != GEO_DEBUG_DATA_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));  ///< 8 bit(s) from B0
  to->GEO_COMPASS_Calibration = ((raw));
  raw = ((uint32_t)((bytes[1])));         ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 8;   ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 16;  ///< 8 bit(s) from B24
  raw |= ((uint32_t)((bytes[4]))) << 24;  ///< 8 bit(s) from B32
  to->GEO_COMPASS_Heading = ((raw * 0.1));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode SENSOR's 'SENSOR_DATA' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_SENSOR_DATA(SENSOR_DATA_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != SENSOR_DATA_HDR.dlc || hdr->mid != SENSOR_DATA_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0]) & 0x01));  ///< 1 bit(s) from B0
  to->SENSOR_DATA_LeftBumper = ((raw));
  raw = ((uint32_t)((bytes[0] >> 1) & 0x01));  ///< 1 bit(s) from B1
  to->SENSOR_DATA_RightBumper = ((raw));
  raw = ((uint32_t)((bytes[1])));  ///< 8 bit(s) from B8
  to->SENSOR_DATA_LeftUltrasonic = ((raw));
  raw = ((uint32_t)((bytes[2])));  ///< 8 bit(s) from B16
  to->SENSOR_DATA_RightUltrasonic = ((raw));
  raw = ((uint32_t)((bytes[3])));        ///< 8 bit(s) from B24
  raw |= ((uint32_t)((bytes[4]))) << 8;  ///< 8 bit(s) from B32
  to->SENSOR_DATA_MiddleUltrasonic = ((raw));
  raw = ((uint32_t)((bytes[5])));        ///< 8 bit(s) from B40
  raw |= ((uint32_t)((bytes[6]))) << 8;  ///< 8 bit(s) from B48
  to->SENSOR_DATA_RearIr = ((raw));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode BRIDGE's 'BRIDGE_DATA_CMD' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_BRIDGE_DATA_CMD(BRIDGE_DATA_CMD_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != BRIDGE_DATA_CMD_HDR.dlc || hdr->mid != BRIDGE_DATA_CMD_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0]) & 0x01));  ///< 1 bit(s) from B0
  to->BRIDGE_DATA_CMD_start_stop = ((raw));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode BRIDGE's 'BRIDGE_CHECKPOINT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_BRIDGE_CHECKPOINT(BRIDGE_CHECKPOINT_t *to, const uint8_t bytes[8],
                                                const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != BRIDGE_CHECKPOINT_HDR.dlc || hdr->mid != BRIDGE_CHECKPOINT_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  to->BRIDGE_DATA_Latitude = ((raw * 1e-08));
  raw = ((uint32_t)((bytes[4])));         ///< 8 bit(s) from B32
  raw |= ((uint32_t)((bytes[5]))) << 8;   ///< 8 bit(s) from B40
  raw |= ((uint32_t)((bytes[6]))) << 16;  ///< 8 bit(s) from B48
  raw |= ((uint32_t)((bytes[7]))) << 24;  ///< 8 bit(s) from B56
  to->BRIDGE_DATA_Longitude = ((raw * 1e-07) + (-150));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_DATA' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_DATA(MOTOR_DATA_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != MOTOR_DATA_HDR.dlc || hdr->mid != MOTOR_DATA_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));  ///< 8 bit(s) from B0
  if (raw & (1 << 7)) {            // Check signed bit
    to->MOTOR_DATA_steer = ((((0xFFFFFFFF << 7) | raw)));
  } else {
    to->MOTOR_DATA_steer = ((raw));
  }
  raw = ((uint32_t)((bytes[1])));        ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 8;  ///< 8 bit(s) from B16
  to->MOTOR_DATA_speed = ((raw * 0.1));
  raw = ((uint32_t)((bytes[3]) & 0x03));  ///< 2 bit(s) from B24
  to->MOTOR_DATA_direction = (MOTOR_DATA_direction_E)((raw));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_DEBUG_RPM_PARTIAL' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_DEBUG_RPM_PARTIAL(MOTOR_DEBUG_RPM_PARTIAL_t *to, const uint8_t bytes[8],
                                                      const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != MOTOR_DEBUG_RPM_PARTIAL_HDR.dlc || hdr->mid != MOTOR_DEBUG_RPM_PARTIAL_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  if (raw & (1 << 31)) {                  // Check signed bit
    to->MOTOR_DEBUG_rpm_part = ((((0xFFFFFFFF << 31) | raw)));
  } else {
    to->MOTOR_DEBUG_rpm_part = ((raw));
  }

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_DEBUG_RPM_ACTUAL' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_DEBUG_RPM_ACTUAL(MOTOR_DEBUG_RPM_ACTUAL_t *to, const uint8_t bytes[8],
                                                     const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != MOTOR_DEBUG_RPM_ACTUAL_HDR.dlc || hdr->mid != MOTOR_DEBUG_RPM_ACTUAL_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  if (raw & (1 << 31)) {                  // Check signed bit
    to->MOTOR_DEBUG_rpm_act = ((((0xFFFFFFFF << 31) | raw) * 0.01));
  } else {
    to->MOTOR_DEBUG_rpm_act = ((raw * 0.01));
  }

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_DEBUG_PI_ERROR' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_DEBUG_PI_ERROR(MOTOR_DEBUG_PI_ERROR_t *to, const uint8_t bytes[8],
                                                   const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != MOTOR_DEBUG_PI_ERROR_HDR.dlc || hdr->mid != MOTOR_DEBUG_PI_ERROR_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  if (raw & (1 << 31)) {                  // Check signed bit
    to->MOTOR_DEBUG_pi_err = ((((0xFFFFFFFF << 31) | raw) * 0.01));
  } else {
    to->MOTOR_DEBUG_pi_err = ((raw * 0.01));
  }

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_DEBUG_LARGE_ERROR_CNT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_DEBUG_LARGE_ERROR_CNT(MOTOR_DEBUG_LARGE_ERROR_CNT_t *to, const uint8_t bytes[8],
                                                          const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr &&
      (hdr->dlc != MOTOR_DEBUG_LARGE_ERROR_CNT_HDR.dlc || hdr->mid != MOTOR_DEBUG_LARGE_ERROR_CNT_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  to->MOTOR_DEBUG_lg_err_cnt = ((raw));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_DEBUG_PROPORTIONAL_CMD' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_DEBUG_PROPORTIONAL_CMD(MOTOR_DEBUG_PROPORTIONAL_CMD_t *to, const uint8_t bytes[8],
                                                           const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr &&
      (hdr->dlc != MOTOR_DEBUG_PROPORTIONAL_CMD_HDR.dlc || hdr->mid != MOTOR_DEBUG_PROPORTIONAL_CMD_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  if (raw & (1 << 31)) {                  // Check signed bit
    to->MOTOR_DEBUG_prop_cmd = ((((0xFFFFFFFF << 31) | raw) * 0.01));
  } else {
    to->MOTOR_DEBUG_prop_cmd = ((raw * 0.01));
  }

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_DEBUG_INTEGRAL_CMD' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_DEBUG_INTEGRAL_CMD(MOTOR_DEBUG_INTEGRAL_CMD_t *to, const uint8_t bytes[8],
                                                       const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != MOTOR_DEBUG_INTEGRAL_CMD_HDR.dlc || hdr->mid != MOTOR_DEBUG_INTEGRAL_CMD_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  if (raw & (1 << 31)) {                  // Check signed bit
    to->MOTOR_DEBUG_int_cmd = ((((0xFFFFFFFF << 31) | raw) * 0.01));
  } else {
    to->MOTOR_DEBUG_int_cmd = ((raw * 0.01));
  }

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_DEBUG_INTEGRAL_CMD_OLD' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_DEBUG_INTEGRAL_CMD_OLD(MOTOR_DEBUG_INTEGRAL_CMD_OLD_t *to, const uint8_t bytes[8],
                                                           const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr &&
      (hdr->dlc != MOTOR_DEBUG_INTEGRAL_CMD_OLD_HDR.dlc || hdr->mid != MOTOR_DEBUG_INTEGRAL_CMD_OLD_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  if (raw & (1 << 31)) {                  // Check signed bit
    to->MOTOR_DEBUG_int_cmd_old = ((((0xFFFFFFFF << 31) | raw) * 0.01));
  } else {
    to->MOTOR_DEBUG_int_cmd_old = ((raw * 0.01));
  }

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_DEBUG_OUTPUT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_DEBUG_OUTPUT(MOTOR_DEBUG_OUTPUT_t *to, const uint8_t bytes[8],
                                                 const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != MOTOR_DEBUG_OUTPUT_HDR.dlc || hdr->mid != MOTOR_DEBUG_OUTPUT_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  if (raw & (1 << 31)) {                  // Check signed bit
    to->MOTOR_DEBUG_out = ((((0xFFFFFFFF << 31) | raw) * 0.01));
  } else {
    to->MOTOR_DEBUG_out = ((raw * 0.01));
  }

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Decode MOTOR's 'MOTOR_DEBUG_PWM_ACTUAL' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MOTOR_DEBUG_PWM_ACTUAL(MOTOR_DEBUG_PWM_ACTUAL_t *to, const uint8_t bytes[8],
                                                     const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != MOTOR_DEBUG_PWM_ACTUAL_HDR.dlc || hdr->mid != MOTOR_DEBUG_PWM_ACTUAL_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));         ///< 8 bit(s) from B0
  raw |= ((uint32_t)((bytes[1]))) << 8;   ///< 8 bit(s) from B8
  raw |= ((uint32_t)((bytes[2]))) << 16;  ///< 8 bit(s) from B16
  raw |= ((uint32_t)((bytes[3]))) << 24;  ///< 8 bit(s) from B24
  if (raw & (1 << 31)) {                  // Check signed bit
    to->MOTOR_DEBUG_pwm_act = ((((0xFFFFFFFF << 31) | raw) * 0.01));
  } else {
    to->MOTOR_DEBUG_pwm_act = ((raw * 0.01));
  }

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Not generating code for dbc_decode_MASTER_DRIVE_CMD() since 'MASTER' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MASTER_DEBUG() since 'MASTER' is not the recipient of any of the signals

/// Handle the MIA for GEO's GEO_HEARTBEAT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_GEO_HEARTBEAT(GEO_HEARTBEAT_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= GEO_HEARTBEAT__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = GEO_HEARTBEAT__MIA_MSG;
    msg->mia_info.mia_counter_ms = GEO_HEARTBEAT__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for SENSOR's SENSOR_HEARTBEAT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_SENSOR_HEARTBEAT(SENSOR_HEARTBEAT_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= SENSOR_HEARTBEAT__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = SENSOR_HEARTBEAT__MIA_MSG;
    msg->mia_info.mia_counter_ms = SENSOR_HEARTBEAT__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for BRIDGE's BRIDGE_HEARTBEAT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_BRIDGE_HEARTBEAT(BRIDGE_HEARTBEAT_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= BRIDGE_HEARTBEAT__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = BRIDGE_HEARTBEAT__MIA_MSG;
    msg->mia_info.mia_counter_ms = BRIDGE_HEARTBEAT__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_HEARTBEAT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_HEARTBEAT(MOTOR_HEARTBEAT_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_HEARTBEAT__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_HEARTBEAT__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_HEARTBEAT__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for GEO's GEO_COORDINATE_DATA message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_GEO_COORDINATE_DATA(GEO_COORDINATE_DATA_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= GEO_COORDINATE_DATA__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = GEO_COORDINATE_DATA__MIA_MSG;
    msg->mia_info.mia_counter_ms = GEO_COORDINATE_DATA__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for GEO's GEO_DATA message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_GEO_DATA(GEO_DATA_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= GEO_DATA__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = GEO_DATA__MIA_MSG;
    msg->mia_info.mia_counter_ms = GEO_DATA__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for GEO's GEO_DEBUG_DATA message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_GEO_DEBUG_DATA(GEO_DEBUG_DATA_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= GEO_DEBUG_DATA__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = GEO_DEBUG_DATA__MIA_MSG;
    msg->mia_info.mia_counter_ms = GEO_DEBUG_DATA__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for SENSOR's SENSOR_DATA message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_SENSOR_DATA(SENSOR_DATA_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= SENSOR_DATA__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = SENSOR_DATA__MIA_MSG;
    msg->mia_info.mia_counter_ms = SENSOR_DATA__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for BRIDGE's BRIDGE_DATA_CMD message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_BRIDGE_DATA_CMD(BRIDGE_DATA_CMD_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= BRIDGE_DATA_CMD__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = BRIDGE_DATA_CMD__MIA_MSG;
    msg->mia_info.mia_counter_ms = BRIDGE_DATA_CMD__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for BRIDGE's BRIDGE_CHECKPOINT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_BRIDGE_CHECKPOINT(BRIDGE_CHECKPOINT_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= BRIDGE_CHECKPOINT__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = BRIDGE_CHECKPOINT__MIA_MSG;
    msg->mia_info.mia_counter_ms = BRIDGE_CHECKPOINT__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_DATA message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_DATA(MOTOR_DATA_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_DATA__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_DATA__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_DATA__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_DEBUG_RPM_PARTIAL message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_DEBUG_RPM_PARTIAL(MOTOR_DEBUG_RPM_PARTIAL_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_DEBUG_RPM_PARTIAL__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_DEBUG_RPM_PARTIAL__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_DEBUG_RPM_PARTIAL__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_DEBUG_RPM_ACTUAL message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_DEBUG_RPM_ACTUAL(MOTOR_DEBUG_RPM_ACTUAL_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_DEBUG_RPM_ACTUAL__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_DEBUG_RPM_ACTUAL__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_DEBUG_RPM_ACTUAL__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_DEBUG_PI_ERROR message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_DEBUG_PI_ERROR(MOTOR_DEBUG_PI_ERROR_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_DEBUG_PI_ERROR__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_DEBUG_PI_ERROR__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_DEBUG_PI_ERROR__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_DEBUG_LARGE_ERROR_CNT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_DEBUG_LARGE_ERROR_CNT(MOTOR_DEBUG_LARGE_ERROR_CNT_t *msg,
                                                              uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_DEBUG_LARGE_ERROR_CNT__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_DEBUG_LARGE_ERROR_CNT__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_DEBUG_LARGE_ERROR_CNT__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_DEBUG_PROPORTIONAL_CMD message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_DEBUG_PROPORTIONAL_CMD(MOTOR_DEBUG_PROPORTIONAL_CMD_t *msg,
                                                               uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_DEBUG_PROPORTIONAL_CMD__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_DEBUG_PROPORTIONAL_CMD__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_DEBUG_PROPORTIONAL_CMD__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_DEBUG_INTEGRAL_CMD message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_DEBUG_INTEGRAL_CMD(MOTOR_DEBUG_INTEGRAL_CMD_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_DEBUG_INTEGRAL_CMD__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_DEBUG_INTEGRAL_CMD__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_DEBUG_INTEGRAL_CMD__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_DEBUG_INTEGRAL_CMD_OLD message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_DEBUG_INTEGRAL_CMD_OLD(MOTOR_DEBUG_INTEGRAL_CMD_OLD_t *msg,
                                                               uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_DEBUG_INTEGRAL_CMD_OLD__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_DEBUG_INTEGRAL_CMD_OLD__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_DEBUG_INTEGRAL_CMD_OLD__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_DEBUG_OUTPUT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_DEBUG_OUTPUT(MOTOR_DEBUG_OUTPUT_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_DEBUG_OUTPUT__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_DEBUG_OUTPUT__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_DEBUG_OUTPUT__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

/// Handle the MIA for MOTOR's MOTOR_DEBUG_PWM_ACTUAL message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MOTOR_DEBUG_PWM_ACTUAL(MOTOR_DEBUG_PWM_ACTUAL_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MOTOR_DEBUG_PWM_ACTUAL__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = MOTOR_DEBUG_PWM_ACTUAL__MIA_MSG;
    msg->mia_info.mia_counter_ms = MOTOR_DEBUG_PWM_ACTUAL__MIA_MS;
    msg->mia_info.is_mia = true;
    mia_occurred = true;
  }

  return mia_occurred;
}

#endif
