#include "unity.h"

#include "navigation.h"

navigation_state_machine_S state_variables;
navigation_sensors_S sensor_data;
navigation_motor_cmd_S motor_command;
GEO_DATA_t geo_data;

/******************************************************************************
 *
 * CONSTANTS
 *
 ******************************************************************************/
extern const uint8_t STEER_THRESHOLD_CM;
extern const uint8_t MIDDLE_THRESHOLD_FAR;
extern const uint8_t MIDDLE_THRESHOLD_CLOSE;
extern const uint8_t REVERSE_THRESHOLD;

extern const uint8_t MOTOR_STOP;
extern const uint8_t MOTOR_FORWARD;
extern const uint8_t MOTOR_REVERSE;

extern const float NAVIGATION_SPEED;
extern const float OBSTACLE_SPEED;

extern const int16_t STEER_STRAIGHT;
extern const int16_t STEER_OBSTACLE;

void setUp(void) { init_navigation(&state_variables, &sensor_data, &geo_data, &motor_command); }

void tearDown(void) {}

void test_init_navigation(void) {
  TEST_ASSERT_FALSE(state_variables.go);
  TEST_ASSERT_EQUAL(state_variables.state, INIT);

  TEST_ASSERT_TRUE(sensor_data.left_bumper_triggered & sensor_data.right_bumper_triggered);
  TEST_ASSERT_FALSE(sensor_data.left_ultrasonic_cm & sensor_data.right_ultrasonic_cm &
                    sensor_data.middle_ultrasonic_cm & sensor_data.rear_ir_cm);

  TEST_ASSERT_EQUAL(motor_command.motor_speed, 0);
  TEST_ASSERT_EQUAL(motor_command.steer_direction, 0);
  TEST_ASSERT_EQUAL(motor_command.motor_direction, 0);
}

void test_navigation_state_machine(void) {
  // start in init
  TEST_ASSERT_EQUAL(INIT, state_variables.state);
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(WAIT, state_variables.state);
  TEST_ASSERT_EQUAL(0, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(0, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(0, motor_command.motor_direction);

  // transition to wait always
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(WAIT, state_variables.state);
  TEST_ASSERT_EQUAL(0, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(0, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(0, motor_command.motor_direction);

  // transition to navigate on go
  state_variables.go = true;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(NAVIGATE, state_variables.state);
  TEST_ASSERT_EQUAL(0, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(0, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(0, motor_command.motor_direction);

  // drive straight at nav speed, if sensors are good
  sensor_data.left_ultrasonic_cm = STEER_THRESHOLD_CM;
  sensor_data.right_ultrasonic_cm = STEER_THRESHOLD_CM;
  sensor_data.middle_ultrasonic_cm = MIDDLE_THRESHOLD_FAR;
  sensor_data.rear_ir_cm = REVERSE_THRESHOLD;
  //  sensor_data.left_bumper_triggered = true;
  //  sensor_data.right_bumper_triggered = true;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(NAVIGATE, state_variables.state);
  TEST_ASSERT_EQUAL(NAVIGATION_SPEED, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(STEER_STRAIGHT, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_FORWARD, motor_command.motor_direction);

  // steer based on geo input
  geo_data.GEO_DATA_Angle = 56;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(NAVIGATE, state_variables.state);
  TEST_ASSERT_EQUAL(NAVIGATION_SPEED, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(14, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_FORWARD, motor_command.motor_direction);

  // obstacle left
  geo_data.GEO_DATA_Angle = 0.0;
  sensor_data.left_ultrasonic_cm = STEER_THRESHOLD_CM - 1;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(OBSTACLE_LEFT, state_variables.state);

  // right obstacle closer than left
  sensor_data.right_ultrasonic_cm = STEER_THRESHOLD_CM - 2;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(OBSTACLE_RIGHT, state_variables.state);
  TEST_ASSERT_EQUAL(OBSTACLE_SPEED, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(STEER_OBSTACLE, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_FORWARD, motor_command.motor_direction);

  // far obstacle straight
  sensor_data.middle_ultrasonic_cm = MIDDLE_THRESHOLD_FAR - 1;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(OBSTACLE_RIGHT, state_variables.state);
  TEST_ASSERT_EQUAL(OBSTACLE_SPEED, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(-STEER_OBSTACLE, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_FORWARD, motor_command.motor_direction);

  // close obstacle straight
  sensor_data.middle_ultrasonic_cm = MIDDLE_THRESHOLD_CLOSE - 1;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(OBSTACLE_MIDDLE_CLOSE, state_variables.state);
  TEST_ASSERT_EQUAL(OBSTACLE_SPEED, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(-STEER_OBSTACLE, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_FORWARD, motor_command.motor_direction);

  // close obstacle straight, with reverse obstacle
  sensor_data.rear_ir_cm = REVERSE_THRESHOLD - 1;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(OBSTACLE_MIDDLE_CLOSE, state_variables.state);
  TEST_ASSERT_EQUAL(0, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(STEER_STRAIGHT, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_STOP, motor_command.motor_direction);

  // close obstacle straight, no reverse obstacle
  sensor_data.rear_ir_cm = REVERSE_THRESHOLD;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(OBSTACLE_MIDDLE_CLOSE, state_variables.state);
  TEST_ASSERT_EQUAL(OBSTACLE_SPEED, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(STEER_STRAIGHT, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_REVERSE, motor_command.motor_direction);

  // no more obstacles
  sensor_data.left_ultrasonic_cm = STEER_THRESHOLD_CM;
  sensor_data.right_ultrasonic_cm = STEER_THRESHOLD_CM;
  sensor_data.middle_ultrasonic_cm = MIDDLE_THRESHOLD_FAR;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(NAVIGATE, state_variables.state);
  TEST_ASSERT_EQUAL(OBSTACLE_SPEED, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(STEER_STRAIGHT, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_REVERSE, motor_command.motor_direction);

  // bump trigger
  sensor_data.left_bumper_triggered = false;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(OBSTACLE_MIDDLE_CLOSE, state_variables.state);
  TEST_ASSERT_EQUAL(NAVIGATION_SPEED, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(STEER_STRAIGHT, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_FORWARD, motor_command.motor_direction);

  // no more obstacles
  sensor_data.left_bumper_triggered = true;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(NAVIGATE, state_variables.state);
  TEST_ASSERT_EQUAL(OBSTACLE_SPEED, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(STEER_STRAIGHT, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_REVERSE, motor_command.motor_direction);

  // check default state
  state_variables.state = 500;
  navigation_state_machine(&state_variables, sensor_data, geo_data, &motor_command);
  TEST_ASSERT_EQUAL(WAIT, state_variables.state);
  TEST_ASSERT_EQUAL(0, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(0, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(0, motor_command.motor_direction);
}

void test_steer_processing(void) {
  steer_processing(&state_variables, sensor_data);
  TEST_ASSERT_EQUAL(OBSTACLE_RIGHT, state_variables.state);

  sensor_data.right_ultrasonic_cm = STEER_THRESHOLD_CM;
  steer_processing(&state_variables, sensor_data);
  TEST_ASSERT_EQUAL(OBSTACLE_LEFT, state_variables.state);

  sensor_data.right_ultrasonic_cm = STEER_THRESHOLD_CM - 1;
  sensor_data.left_ultrasonic_cm = STEER_THRESHOLD_CM;
  steer_processing(&state_variables, sensor_data);
  TEST_ASSERT_EQUAL(OBSTACLE_RIGHT, state_variables.state);

  sensor_data.right_ultrasonic_cm = STEER_THRESHOLD_CM;
  steer_processing(&state_variables, sensor_data);
  TEST_ASSERT_EQUAL(NAVIGATE, state_variables.state);
}

void test_set_motor_command(void) {
  set_motor_command(&motor_command, MOTOR_FORWARD, NAVIGATION_SPEED, STEER_STRAIGHT);
  TEST_ASSERT_EQUAL(NAVIGATION_SPEED, motor_command.motor_speed);
  TEST_ASSERT_EQUAL(STEER_STRAIGHT, motor_command.steer_direction);
  TEST_ASSERT_EQUAL(MOTOR_FORWARD, motor_command.motor_direction);
}

void test_front_bump_processing(void) {
  sensor_data.left_bumper_triggered = true;
  sensor_data.right_bumper_triggered = true;
  front_bump_processing(&state_variables, sensor_data);
  TEST_ASSERT_EQUAL(INIT, state_variables.state);

  sensor_data.left_bumper_triggered = false;
  front_bump_processing(&state_variables, sensor_data);
  TEST_ASSERT_EQUAL(OBSTACLE_MIDDLE_CLOSE, state_variables.state);

  state_variables.state = INIT;
  sensor_data.right_bumper_triggered = false;
  front_bump_processing(&state_variables, sensor_data);
  TEST_ASSERT_EQUAL(OBSTACLE_MIDDLE_CLOSE, state_variables.state);

  state_variables.state = INIT;
  sensor_data.left_bumper_triggered = false;
  sensor_data.right_bumper_triggered = false;
  front_bump_processing(&state_variables, sensor_data);
  TEST_ASSERT_EQUAL(OBSTACLE_MIDDLE_CLOSE, state_variables.state);
}

void test_geo_steering(void) {
  TEST_ASSERT_EQUAL(0.0, geo_steering(geo_data));

  geo_data.GEO_DATA_Angle = -5;
  TEST_ASSERT_EQUAL(0.0, geo_steering(geo_data));

  geo_data.GEO_DATA_Angle = 5;
  TEST_ASSERT_EQUAL(0.0, geo_steering(geo_data));

  geo_data.GEO_DATA_Angle = -5.1;
  TEST_ASSERT_EQUAL(-1.275, geo_steering(geo_data));

  geo_data.GEO_DATA_Angle = 5.1;
  TEST_ASSERT_EQUAL(1.275, geo_steering(geo_data));

  geo_data.GEO_DATA_Angle = 500;
  TEST_ASSERT_EQUAL(45, geo_steering(geo_data));

  geo_data.GEO_DATA_Angle = -624;
  TEST_ASSERT_EQUAL(-45, geo_steering(geo_data));
}
