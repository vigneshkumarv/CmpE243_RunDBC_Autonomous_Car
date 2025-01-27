// navigation.c
/******************************************************************************
 *
 * STANDARD INCLUDES
 *
 ******************************************************************************/

/******************************************************************************
 *
 * CUSTOM INCLUDES
 *
 ******************************************************************************/
#include "navigation.h"

/******************************************************************************
 *
 * GLOBAL VARIABLES
 *
 ******************************************************************************/
static float nav_speed = 0;

/******************************************************************************
 *
 * CONSTANTS
 *
 ******************************************************************************/
const uint8_t STEER_THRESHOLD_CM = 100;
const uint8_t MIDDLE_THRESHOLD_FAR = 75;
const uint8_t MIDDLE_THRESHOLD_CLOSE = 35;
const uint8_t REVERSE_THRESHOLD = 35;

const uint8_t MOTOR_STOP = 0;
const uint8_t MOTOR_FORWARD = 1;
const uint8_t MOTOR_REVERSE = 2;

const float NAVIGATION_SPEED = 2.0;
const float OBSTACLE_SPEED = 1.25;
const float REVERSE_SPEED = .5;

const int16_t STEER_STRAIGHT = 0;
const int16_t STEER_OBSTACLE = 25;

const uint32_t REVERSE_PAUSE_COUNT = 50;

/******************************************************************************
 *
 * PUBLIC FUNCTIONS
 *
 ******************************************************************************/
void init_navigation(navigation_state_machine_S* state_variables, navigation_sensors_S* sensor_data,
                     GEO_DATA_t* geo_data, navigation_motor_cmd_S* motor_command) {
  state_variables->go = false;
  state_variables->state = INIT;

  sensor_data->left_bumper_triggered = true;
  sensor_data->right_bumper_triggered = true;
  sensor_data->left_ultrasonic_cm = 0;
  sensor_data->right_ultrasonic_cm = 0;
  sensor_data->middle_ultrasonic_cm = 0;
  sensor_data->rear_ir_cm = 0;

  geo_data->GEO_DATA_Angle = 0.0;
  geo_data->GEO_DATA_Distance = 0.0;

  motor_command->motor_speed = 0;
  motor_command->steer_direction = 0;
  motor_command->motor_direction = 0;
}

void navigation_state_machine(uint32_t count, navigation_state_machine_S* state_variables,
                              navigation_sensors_S sensor_data, GEO_DATA_t geo_data,
                              navigation_motor_cmd_S* motor_command) {
  static uint32_t initial_count = 0;
  switch (state_variables->state) {
    case INIT:
      set_motor_command(motor_command, MOTOR_STOP, 0, STEER_STRAIGHT);
      state_variables->state = WAIT;
      break;
    case WAIT:
      set_motor_command(motor_command, MOTOR_STOP, 0, STEER_STRAIGHT);
      if (state_variables->go && (geo_data.GEO_DATA_Distance >= 10)) {
        state_variables->state = NAVIGATE;
      }
      break;
    case NAVIGATE:
      steer_processing(state_variables, sensor_data);
      front_obstacle_processing(state_variables, sensor_data);
      front_bump_processing(state_variables, sensor_data);
      int16_t nav_steer_angle = geo_steering(geo_data);
      set_motor_command(motor_command, MOTOR_FORWARD, nav_speed, nav_steer_angle);

      // test drive straight
      //      set_motor_command(motor_command, MOTOR_FORWARD, NAVIGATION_SPEED, STEER_STRAIGHT);
      if (!state_variables->go | (geo_data.GEO_DATA_Distance < 10)) {
        state_variables->state = WAIT;
      }
      break;
    case OBSTACLE_RIGHT:
      steer_processing(state_variables, sensor_data);
      if ((sensor_data.middle_ultrasonic_cm < MIDDLE_THRESHOLD_CLOSE) | !sensor_data.left_bumper_triggered |
          !sensor_data.right_bumper_triggered) {
        state_variables->state = OBSTACLE_MIDDLE_CLOSE;
      }
      set_motor_command(motor_command, MOTOR_FORWARD, OBSTACLE_SPEED, (-1 * STEER_OBSTACLE));

      // code re-use (refactor to a function) onthis branch statment
      if (!state_variables->go | (geo_data.GEO_DATA_Distance < 10)) {
        state_variables->state = WAIT;
      }
      break;

    case OBSTACLE_LEFT:
      steer_processing(state_variables, sensor_data);
      if ((sensor_data.middle_ultrasonic_cm < MIDDLE_THRESHOLD_CLOSE) | !sensor_data.left_bumper_triggered |
          !sensor_data.right_bumper_triggered) {
        state_variables->state = OBSTACLE_MIDDLE_CLOSE;
      }
      set_motor_command(motor_command, MOTOR_FORWARD, OBSTACLE_SPEED, STEER_OBSTACLE);
      if (!state_variables->go | (geo_data.GEO_DATA_Distance < 10)) {
        state_variables->state = WAIT;
      }
      break;

    case OBSTACLE_MIDDLE_FAR:
      steer_processing(state_variables, sensor_data);
      front_obstacle_processing(state_variables, sensor_data);
      front_bump_processing(state_variables, sensor_data);
      set_motor_command(motor_command, MOTOR_FORWARD, OBSTACLE_SPEED, STEER_OBSTACLE);
      if (!state_variables->go | (geo_data.GEO_DATA_Distance < 10)) {
        state_variables->state = WAIT;
      }
      break;
    case OBSTACLE_MIDDLE_CLOSE:
      steer_processing(state_variables, sensor_data);
      front_obstacle_processing(state_variables, sensor_data);
      if (sensor_data.rear_ir_cm < REVERSE_THRESHOLD) {
        set_motor_command(motor_command, MOTOR_STOP, 0, STEER_STRAIGHT);
      } else {
        //        set_motor_command(motor_command, MOTOR_STOP, 0, STEER_STRAIGHT);
        set_motor_command(motor_command, MOTOR_REVERSE, REVERSE_SPEED, STEER_STRAIGHT);
      }
      if (state_variables->state != OBSTACLE_MIDDLE_CLOSE) {
        state_variables->state = REVERSE_PAUSE;
        initial_count = count;
      }
      if (!state_variables->go | (geo_data.GEO_DATA_Distance < 10)) {
        state_variables->state = WAIT;
      }

      break;
    case REVERSE_PAUSE:
      set_motor_command(motor_command, MOTOR_STOP, 0, STEER_STRAIGHT);
      if (count > (initial_count + REVERSE_PAUSE_COUNT)) {
        steer_processing(state_variables, sensor_data);
        front_obstacle_processing(state_variables, sensor_data);
      }
      break;
    default:
      set_motor_command(motor_command, MOTOR_STOP, 0, STEER_STRAIGHT);
      state_variables->state = WAIT;
      break;
  }
}

/******************************************************************************
 *
 * PRIVATE FUNCTIONS
 *
 ******************************************************************************/

void steer_processing(navigation_state_machine_S* state_variables, navigation_sensors_S sensor_data) {
  if (sensor_data.left_ultrasonic_cm < STEER_THRESHOLD_CM) {
    if (sensor_data.right_ultrasonic_cm <= sensor_data.left_ultrasonic_cm) {
      state_variables->state = OBSTACLE_RIGHT;
    } else {
      state_variables->state = OBSTACLE_LEFT;
    }
  } else if (sensor_data.right_ultrasonic_cm < STEER_THRESHOLD_CM) {
    state_variables->state = OBSTACLE_RIGHT;
  } else {
    state_variables->state = NAVIGATE;
  }
}

void set_motor_command(navigation_motor_cmd_S* motor_command, uint8_t motor_direction, float motor_speed,
                       int16_t steer_direction) {
  motor_command->motor_direction = motor_direction;
  motor_command->motor_speed = motor_speed;
  motor_command->steer_direction = steer_direction;
}

void front_obstacle_processing(navigation_state_machine_S* state_variables, navigation_sensors_S sensor_data) {
  if (sensor_data.middle_ultrasonic_cm < MIDDLE_THRESHOLD_CLOSE) {
    state_variables->state = OBSTACLE_MIDDLE_CLOSE;
  } else if (sensor_data.middle_ultrasonic_cm < MIDDLE_THRESHOLD_FAR) {
    state_variables->state = OBSTACLE_MIDDLE_FAR;
  }
}

void front_bump_processing(navigation_state_machine_S* state_variables, navigation_sensors_S sensor_data) {
  if ((!sensor_data.left_bumper_triggered) | (!sensor_data.right_bumper_triggered)) {
    state_variables->state = OBSTACLE_MIDDLE_CLOSE;
  }
}

int16_t geo_steering(GEO_DATA_t geo_data) {
  int16_t steer_angle = 0;
  if ((geo_data.GEO_DATA_Angle < -2) | (geo_data.GEO_DATA_Angle > 2)) {
    steer_angle = 5 * (geo_data.GEO_DATA_Angle * 45) / 180;
  }
  steer_angle = (steer_angle > 45) ? 45 : steer_angle;
  steer_angle = (steer_angle < -45) ? -45 : steer_angle;

  float steer_speed_redcution = steer_angle / 90;
  if (steer_speed_redcution < 0) {
    steer_speed_redcution *= -1.0;
  }
  nav_speed = NAVIGATION_SPEED * (1 - steer_speed_redcution);

  return steer_angle;
}
