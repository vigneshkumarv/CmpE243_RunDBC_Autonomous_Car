/*
 * c_periodic_callbacks.h
 *
 *  Created on: Feb 16, 2019
 *      Author: reldn_000
 */

#ifndef C_PERIOD_CALLBACKS_H__
#define C_PERIOD_CALLBACKS_H__

#ifdef __cplusplus
extern "C" {
#endif

/*

#ifndef C_PERIODIC_CALLBACKS_H_
#define C_PERIODIC_CALLBACKS_H_
*/
#include <stdbool.h>
#include <stdint.h>
#include "can.h"

can_t sensor_module;

bool c_period_init(void);
bool c_period_reg_tlm(void);

void c_period_1Hz(uint32_t count);
void c_period_10Hz(uint32_t count);
void c_period_100Hz(uint32_t count);
void c_period_1000Hz(uint32_t count);

#ifdef __cplusplus
}
#endif
#endif /* C_PERIOD_CALLBACKS_H__ */

//#endif /* C_PERIODIC_CALLBACKS_H_ */
