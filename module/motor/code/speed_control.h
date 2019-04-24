// speed_control.h

#include <stdbool.h>

typedef struct {
  float meters_per_sec;
  float int_cmd_old;
  bool isBackward;
} speed_control_t;

float get_RPM_from_MPS(float mps);
float get_actual_speed_from_rpm(float rev_per_min);
float get_RPM_100Hz(void);
float get_pwm_for_speed_control(speed_control_t *speed_state);
void check_for_large_error(void);
