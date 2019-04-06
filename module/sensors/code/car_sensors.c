#include "car_sensors.h"
#include "adc0.h"
#include "lpc_sys.h"

extern SENSOR_DATA_t sensor_data;
extern int get_distance_cm_left_ultrasonic();
extern int get_distance_cm_right_ultrasonic();
extern void set_distance_cm_left_ultrasonic(int cm);
extern void set_distance_cm_right_ultrasonic(int cm);

/*static int counter_middle_ultrasonic = 0;
static int counter_ir = 0;
static int counter_left_ultrasonic = 0;
static int counter_right_ultrasonic = 0;
static int max_value_left_ultrasonic = 2;
static int max_value_right_ultrasonic = 2;
static int max_value_middle_ultrasonic = 20;
static int second_max_middle_ultrasonic = 20;
static int min_value_middle_ultrasonic = 600;
static int sum_ir = 0;*/

static queue_S left_ultrasonic;
static queue_S right_ultrasonic;
static queue_S middle_ultrasonic;
static queue_S rear_ir;

static int previous_value = 20;

static int sum = 0;
static int counter = 0;

// initialization ultrasonic sensors
void init_sensors(void) {
  // each ultrasonic sensor needs 2 digital i/o pins: trig and echo
  // left ultrasonic sensor: trig: p2.0 echo: p2.1
  // right ultrasonic sensor: trig: p2.2 echo: p2.3
  // middle ultrasonic sensor: AN: P0.26

  // init left and right ultrasonic sensors
  init_left_trig_pin(OUTPUT_MODE);   // setup left trigger pin
  init_left_echo_pin(INPUT_MODE);    // setup left echo pin
  init_right_trig_pin(OUTPUT_MODE);  // setup right trigger pin
  init_right_echo_pin(INPUT_MODE);   // setup right echo pin
  init_middle_an_pin();
  init_rear_an_pin();
  init_left_bumper();
  init_right_bumper();

  queue__init(&left_ultrasonic);
  queue__init(&right_ultrasonic);
  queue__init(&middle_ultrasonic);
  queue__init(&rear_ir);
}

// bump sensor (left and right)
// bool is_bump_sensor_pressed(sensor_position whichSensor) {}

// ultrasonic sensor (left, right middle)
void distance_sensor_read(sensor_position whichSensor) {
  // unsigned long timeout = 23324; //this refers to a distance of 4 meters
  // int distance_middle_ultrasonic = 0;
  // int distance_rear_ir = 0;
  switch (whichSensor) {
    case left:
      left_trig_pin_set(low);  // Make sure that trigger pin is LOW.
      delay_us(2);
      left_trig_pin_set(high);  // Hold trigger for 10 microseconds, which is signal for sensor to measure distance.
      delay_us(10);
      left_trig_pin_set(low);
      delay_ms(1);
      delay_us(500);
      calibrate_sensors(left);
      break;

    case right:
      right_trig_pin_set(low);  // Make sure that trigger pin is LOW.
      delay_us(2);
      right_trig_pin_set(high);  // Hold trigger for 10 microseconds, which is signal for sensor to measure distance.
      delay_us(10);
      right_trig_pin_set(low);

      delay_ms(1);
      delay_us(500);
      calibrate_sensors(right);
      break;

    case middle:
      calibrate_sensors(middle);
      break;

    default:  // rear sensor
      calibrate_sensors(rear);
      break;
  }
}

void bumper_sensor_read(sensor_position whichSensor) {
  if (whichSensor == left) {
    sensor_data.SENSOR_DATA_LeftBumper = read_bumper_sensor_pin_left();
    // printf("left bumper: %d ",sensor_data.SENSOR_DATA_LeftBumper);
  } else {
    sensor_data.SENSOR_DATA_RightBumper = read_bumper_sensor_pin_right();
    // printf("right bumper: %d \n",sensor_data.SENSOR_DATA_RightBumper);
  }
}

void calibrate_sensors(sensor_position whichSensor) {
  if (whichSensor == left) {
    int distance = queue__update_and_get_average(&left_ultrasonic, get_distance_cm_left_ultrasonic());
    set_distance_cm_left_ultrasonic(distance);
    sensor_data.SENSOR_DATA_LeftUltrasonic = distance;
    printf("left: %d ", distance);
  } else if (whichSensor == right) {
    int distance = queue__update_and_get_average(&right_ultrasonic, get_distance_cm_right_ultrasonic());
    set_distance_cm_right_ultrasonic(distance);
    sensor_data.SENSOR_DATA_RightUltrasonic = distance;
    printf("right: %d \n", distance);
  } else if (whichSensor == rear) {
    int ir_value = 227648 * pow(adc0_get_reading(5), -1.27);
    int average = queue__update_and_get_average(&rear_ir, ir_value);
    sensor_data.SENSOR_DATA_RearIr = average;
    printf("rear: %d \n", average);
  }

  else if (whichSensor == middle) {

      int middle_value = 0.3182 * adc0_get_reading(4) - 0.3959;
      int average = queue__update_and_get_average(&middle_ultrasonic, middle_value);
      sensor_data.SENSOR_DATA_MiddleUltrasonic = average;
      printf("middle: %dcm \n", average);

    //int current_value = (adc0_get_reading(4) * 0.5 * 2.54 * (1024.0 / 4096.0) / 1.5);
    // printf("individual value: %d \n", current_value);
    /*
    counter++;
    if (counter <= 20){
        int current_value = adc0_get_reading(4);
        sum += current_value;

    }
    if (counter == 20){
        int average = sum / 20;
        printf("Middle average ADC value: %d\n", average);
        sum = 0;
        counter = 0;
    }
*/
    /*
    if (current_value < 20) {
      current_value = 20;
    } else if (current_value >= 600)
      current_value = previous_value;

    queue__update_middle(&middle_ultrasonic, current_value, &max_value, &min_value, &second_max);
    if ((max_value - second_max) > 100) {
      sensor_data.SENSOR_DATA_MiddleUltrasonic = second_max;
      previous_value = second_max;
    } else if ((max_value - second_max) < 100) {
      // sensor_data.SENSOR_DATA_MiddleUltrasonic =(second_max+max_value)/2;
      sensor_data.SENSOR_DATA_MiddleUltrasonic = second_max;
      previous_value = second_max;
    }
    /*
    else {
        sensor_data.SENSOR_DATA_MiddleUltrasonic = min_value;
    }
    */

    //printf("final middle: %d ", sensor_data.SENSOR_DATA_MiddleUltrasonic);
  }
}

/*if (whichSensor == left) {
    counter_left_ultrasonic++;
    if (counter_left_ultrasonic <= 5) {
        int temp = get_distance_cm_left_ultrasonic();
        if (temp > 2) {
            if (temp > max_value_left_ultrasonic) {
                max_value_left_ultrasonic = temp;
            }
        }
    }
    if (counter_left_ultrasonic == 5) {
        max_value_left_ultrasonic = (max_value_left_ultrasonic > 255)? 255 : max_value_left_ultrasonic;
        set_distance_cm_left_ultrasonic(max_value_left_ultrasonic);
        sensor_data.SENSOR_DATA_LeftUltrasonic = max_value_left_ultrasonic;
        printf("left calibrated value: %d \n",max_value_left_ultrasonic);
        counter_left_ultrasonic = 0;
        max_value_left_ultrasonic = 2;
    }
}
else {
    counter_right_ultrasonic++;
    if (counter_right_ultrasonic <= 5) {
        int temp = get_distance_cm_right_ultrasonic();
        if (temp > 2) {
            if (temp > max_value_right_ultrasonic) {
                max_value_right_ultrasonic = temp;
            }
        }
    }
    if (counter_right_ultrasonic == 5) {
        max_value_right_ultrasonic = (max_value_right_ultrasonic > 255)? 255 : max_value_right_ultrasonic;
        set_distance_cm_right_ultrasonic(max_value_right_ultrasonic);
        sensor_data.SENSOR_DATA_RightUltrasonic = max_value_right_ultrasonic;
        printf("right calibrated value: %d \n",max_value_right_ultrasonic);
        counter_right_ultrasonic = 0;
        max_value_right_ultrasonic = 2;
    }
}*/

// middle code:

/*distance_middle_ultrasonic = (adc0_get_reading(4) * 0.5 * 2.54 * (1024.0 / 4096.0) / 1.5);
  counter_middle_ultrasonic++;

  if (counter_middle_ultrasonic <= 5) {

      int temp = distance_middle_ultrasonic;

      if (temp > 20) {
          if (temp > max_value_middle_ultrasonic) {
              second_max_middle_ultrasonic = max_value_middle_ultrasonic;
              max_value_middle_ultrasonic = temp;
          }
          else if (temp > second_max_middle_ultrasonic) {
              second_max_middle_ultrasonic = temp;
          }
          if (temp < min_value_middle_ultrasonic) {
              min_value_middle_ultrasonic = temp;
          }
      }
  }
  if (counter_middle_ultrasonic == 5) {
      if (max_value_middle_ultrasonic > 40) {
          if (!(second_max_middle_ultrasonic == 20)) {
              if ((max_value_middle_ultrasonic - second_max_middle_ultrasonic) < 100) {
                  max_value_middle_ultrasonic = (max_value_middle_ultrasonic + second_max_middle_ultrasonic) / 2.0;
              }
              else
                  max_value_middle_ultrasonic = second_max_middle_ultrasonic;
              sensor_data.SENSOR_DATA_MiddleUltrasonic = max_value_middle_ultrasonic;
          }
          else {
              sensor_data.SENSOR_DATA_MiddleUltrasonic = max_value_middle_ultrasonic;
          }
      }
      else {
          if(min_value_middle_ultrasonic == 600)
              sensor_data.SENSOR_DATA_MiddleUltrasonic = 20;
          else
              sensor_data.SENSOR_DATA_MiddleUltrasonic = min_value_middle_ultrasonic;
      }
      counter_middle_ultrasonic = 0;
      max_value_middle_ultrasonic = 20;
      second_max_middle_ultrasonic = 20;
      min_value_middle_ultrasonic = 600;
      printf("middle distance: %d\n", sensor_data.SENSOR_DATA_MiddleUltrasonic);
  }*/

// rear code:

/*counter_ir++;

           if (counter_ir <= 5) {
               distance_rear_ir = 227648 * pow(adc0_get_reading(5), -1.27);
               int temp = distance_rear_ir;
               sum_ir += temp;
           }
           if (counter_ir == 5) {

               int average = sum_ir / 5;
               printf("rear ir sensor: %d \n", average);

               sensor_data.SENSOR_DATA_RearIr = average;
               counter_ir = 0;
               sum_ir = 0;
           }*/
