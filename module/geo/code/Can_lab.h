/*
 * Can_lab.h
 *
 *  Created on: Mar 24, 2019
 *      Author: 9595v
 */

#ifndef CAN_LAB_H_
#define CAN_LAB_H_
#include "can.h"
#include "C:\Users\9595v\Desktop\autonomous-car\shared_code\wrappers\ls_wrapper.h"

bool Geo_CAN_initialize();

bool Geo_CAN_transmit(can_msg_t *p);

uint8_t Geo_LS_percentage_data();

bool Geo_CAN_reset();

#endif /* CAN_LAB_H_ */



