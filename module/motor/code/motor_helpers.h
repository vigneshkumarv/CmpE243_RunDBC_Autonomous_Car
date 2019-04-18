// motor_helpers.h

#include "motor_controls_master.h"

typedef enum {
  stop,
  forward,
  backward,
} direction_E;

direction_E get_direction(uint8_t direction_raw);
float get_pwm_from_mph(float mph);
void steer_car(int steer_angle);
void move_car(direction_E direction, float mph);


