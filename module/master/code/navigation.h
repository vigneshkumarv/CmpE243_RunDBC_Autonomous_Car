// navigation.h

#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  INIT = 0,
  WAIT,
  NAVIGATE,
  OBSTACLE_RIGHT,
  OBSTACLE_LEFT,
  OBSTACLE_MIDDLE_FAR,
  OBSTACLE_MIDDLE_CLOSE,
} navigation_states_E;

typedef struct {
  bool left_bumper_triggered;
  bool right_bumper_triggered;
  uint8_t left_ultrasonic_cm;
  uint8_t right_ultrasonic_cm;
  uint16_t middle_ultrasonic_cm;
  uint16_t rear_ir_cm;
} navigation_sensors_S;

typedef struct {
  int16_t steer_direction;
  float motor_speed;
  uint8_t motor_direction;
} navigation_motor_cmd_S;

typedef struct {
  navigation_states_E state;
  bool go;
} navigation_state_machine_S;

void init_navigation(navigation_state_machine_S* state_variables, navigation_sensors_S* sensor_data,
                     navigation_motor_cmd_S* motor_command);
void navigation_state_machine(navigation_state_machine_S* state, navigation_sensors_S sensor_data,
                              navigation_motor_cmd_S* motor_command);

/******************************************************************************
 *
 * PRIVATE FUNCTIONS
 *
 ******************************************************************************/
void steer_processing(navigation_state_machine_S* state_variables, navigation_sensors_S sensor_data);
void set_motor_command(navigation_motor_cmd_S* motor_command, uint8_t motor_direction, float motor_speed,
                       int16_t steer_direction);
void front_obstacle_processing(navigation_state_machine_S* state_variables, navigation_sensors_S sensor_data);
void front_bump_processing(navigation_state_machine_S* state_variables, navigation_sensors_S sensor_data);

#endif /* NAVIGATION_H_ */
