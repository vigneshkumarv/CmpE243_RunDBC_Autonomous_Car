#ifndef LIGHT_SPEED_H_
#define LIGHT_SPEED_H_

#include <stdint.h>
#include "can.h"

typedef struct {
  uint8_t GEO_light_percent, BRIDGE_light_percent, SENSOR_light_percent, MOTOR_light_percent;
  uint8_t average_speed_percent;
} light_speed_S;

void init_light_speed(void);
void check_and_restart_can(void);
void update_speed(light_speed_S* speeds);
void send_speed(uint8_t percent_speed);

#endif /* LIGHT_SPEED_H_ */
