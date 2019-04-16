/*
 * bridge_light_sensor_feedback.h
 *
 *  Created on: Mar 24, 2019
 *      Author: lenovo
 */

#ifndef BRIDGE_LIGHT_SENSOR_FEEDBACK_H_
#define BRIDGE_LIGHT_SENSOR_FEEDBACK_H_
#include "generated_can/generated_can.h"
#include "stdbool.h"
#include "stdio.h"

void Bridge_CAN_Init();
void Bridge_CAN_Transmit();
void Bridge_CAN_Check();

#endif /* BRIDGE_LIGHT_SENSOR_FEEDBACK_H_ */
