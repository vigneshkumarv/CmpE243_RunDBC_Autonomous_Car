// obstacle_avoidance.h

#ifndef OBSTACLE_AVOIDANCE_H_
#define OBSTACLE_AVOIDANCE_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  bool left_bumper_triggered;
  bool right_bumper_triggered;
  uint8_t left_ultrasonic_cm;
  uint8_t right_ultrasonic_cm;
  uint16_t middle_ultrasonic_cm;
  uint16_t rear_ir_cm;

  int16_t steer_direction;
  float motor_speed;
  uint8_t motor_direction;
} obstacle_avoidance_S;

bool forward_avoidance(obstacle_avoidance_S* sensor_status);

#endif /* OBSTACLE_AVOIDANCE_H_ */
