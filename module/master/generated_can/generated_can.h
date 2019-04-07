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
static const dbc_msg_hdr_t GEO_DATA_HDR = {769, 1};
static const dbc_msg_hdr_t SENSOR_DATA_HDR = {257, 8};
static const dbc_msg_hdr_t BRIDGE_DATA_HDR = {1025, 1};
static const dbc_msg_hdr_t MOTOR_DATA_HDR = {513, 1};
static const dbc_msg_hdr_t MASTER_DRIVE_CMD_HDR = {1, 4};

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

/// Message: GEO_DATA from 'GEO', DLC: 1 byte(s), MID: 769
typedef struct {
  uint8_t GEO_DATA_cmd;  ///< B7:0   Destination: MASTER

  dbc_mia_info_t mia_info;
} GEO_DATA_t;

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

/// Message: BRIDGE_DATA from 'BRIDGE', DLC: 1 byte(s), MID: 1025
typedef struct {
  uint8_t BRIDGE_DATA_cmd;  ///< B7:0   Destination: MASTER

  dbc_mia_info_t mia_info;
} BRIDGE_DATA_t;

/// Message: MOTOR_DATA from 'MOTOR', DLC: 1 byte(s), MID: 513
typedef struct {
  uint8_t MOTOR_DATA_cmd;  ///< B7:0   Destination: MASTER

  dbc_mia_info_t mia_info;
} MOTOR_DATA_t;

/// Message: MASTER_DRIVE_CMD from 'MASTER', DLC: 4 byte(s), MID: 1
typedef struct {
  int16_t MASTER_DRIVE_CMD_steer;          ///< B7:0   Destination: MOTOR
  float MASTER_DRIVE_CMD_speed;            ///< B23:8   Destination: MOTOR
  uint8_t MASTER_DRIVE_CMD_direction : 2;  ///< B25:24   Destination: MOTOR

  // No dbc_mia_info_t for a message that we will send
} MASTER_DRIVE_CMD_t;

/// @{ These 'externs' need to be defined in a source file of your project
extern const uint32_t GEO_HEARTBEAT__MIA_MS;
extern const GEO_HEARTBEAT_t GEO_HEARTBEAT__MIA_MSG;
extern const uint32_t SENSOR_HEARTBEAT__MIA_MS;
extern const SENSOR_HEARTBEAT_t SENSOR_HEARTBEAT__MIA_MSG;
extern const uint32_t BRIDGE_HEARTBEAT__MIA_MS;
extern const BRIDGE_HEARTBEAT_t BRIDGE_HEARTBEAT__MIA_MSG;
extern const uint32_t MOTOR_HEARTBEAT__MIA_MS;
extern const MOTOR_HEARTBEAT_t MOTOR_HEARTBEAT__MIA_MSG;
extern const uint32_t GEO_DATA__MIA_MS;
extern const GEO_DATA_t GEO_DATA__MIA_MSG;
extern const uint32_t SENSOR_DATA__MIA_MS;
extern const SENSOR_DATA_t SENSOR_DATA__MIA_MSG;
extern const uint32_t BRIDGE_DATA__MIA_MS;
extern const BRIDGE_DATA_t BRIDGE_DATA__MIA_MSG;
extern const uint32_t MOTOR_DATA__MIA_MS;
extern const MOTOR_DATA_t MOTOR_DATA__MIA_MSG;
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

/// Not generating code for dbc_encode_GEO_DATA() since the sender is GEO and we are MASTER

/// Not generating code for dbc_encode_SENSOR_DATA() since the sender is SENSOR and we are MASTER

/// Not generating code for dbc_encode_BRIDGE_DATA() since the sender is BRIDGE and we are MASTER

/// Not generating code for dbc_encode_MOTOR_DATA() since the sender is MOTOR and we are MASTER

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

/// Decode GEO's 'GEO_DATA' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_GEO_DATA(GEO_DATA_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != GEO_DATA_HDR.dlc || hdr->mid != GEO_DATA_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));  ///< 8 bit(s) from B0
  to->GEO_DATA_cmd = ((raw));

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

/// Decode BRIDGE's 'BRIDGE_DATA' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_BRIDGE_DATA(BRIDGE_DATA_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr) {
  const bool success = true;
  // If msg header is provided, check if the DLC and the MID match
  if (NULL != hdr && (hdr->dlc != BRIDGE_DATA_HDR.dlc || hdr->mid != BRIDGE_DATA_HDR.mid)) {
    return !success;
  }

  uint32_t raw;
  raw = ((uint32_t)((bytes[0])));  ///< 8 bit(s) from B0
  to->BRIDGE_DATA_cmd = ((raw));

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
  to->MOTOR_DATA_cmd = ((raw));

  to->mia_info.mia_counter_ms = 0;  ///< Reset the MIA counter

  return success;
}

/// Not generating code for dbc_decode_MASTER_DRIVE_CMD() since 'MASTER' is not the recipient of any of the signals

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

/// Handle the MIA for BRIDGE's BRIDGE_DATA message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_BRIDGE_DATA(BRIDGE_DATA_t *msg, uint32_t time_incr_ms) {
  bool mia_occurred = false;
  const dbc_mia_info_t old_mia = msg->mia_info;
  msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= BRIDGE_DATA__MIA_MS);

  if (!msg->mia_info.is_mia) {  // Not MIA yet, so keep incrementing the MIA counter
    msg->mia_info.mia_counter_ms += time_incr_ms;
  } else if (!old_mia.is_mia) {  // Previously not MIA, but it is MIA now
    // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
    *msg = BRIDGE_DATA__MIA_MSG;
    msg->mia_info.mia_counter_ms = BRIDGE_DATA__MIA_MS;
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

#endif
