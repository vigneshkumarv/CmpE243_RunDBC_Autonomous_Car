// motor_helpers.h

#include "motor_controls_master.h"

typedef enum {
  stop,
  forward,
  backward,
} direction_E;

direction_E get_direction(uint8_t direction_raw);
void steer_car(int steer_angle);
void move_car(direction_E direction, float mps);
void init_speed_state(void);
