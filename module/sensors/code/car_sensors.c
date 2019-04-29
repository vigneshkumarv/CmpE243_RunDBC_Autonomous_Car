#include "car_sensors.h"
#include "adc0.h"
//#include "lpc_sys.h"

static queue_S left_ultrasonic;
static queue_S right_ultrasonic;
static queue_S middle_ultrasonic;
static queue_S rear_ir;


// initialization ultrasonic sensors
void init_sensors(void)
{

    init_middle_an_pin();
    init_rear_an_pin();
    init_left_an_pin();
    init_right_an_pin();
    init_left_bumper();
    init_right_bumper();
    init_gpio_middle_trigger_pin();
    init_gpio_left_right_trigger_pin();
    /*
    gpio_left_right_trigger_set(high);
    delay_us(20);
    gpio_left_right_trigger_set(low);
    */
    queue__init(&left_ultrasonic);
    queue__init(&right_ultrasonic);
    queue__init(&middle_ultrasonic);
    queue__init(&rear_ir);

}

// bump sensor (left and right)
// bool is_bump_sensor_pressed(sensor_position whichSensor) {}

// ultrasonic sensor (left, right middle)

void distance_sensor_read(sensor_position whichSensor)
{

    switch (whichSensor) {
        case left:

            calibrate_sensors(left);
            break;

        case right:
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

void bumper_sensor_read(sensor_position whichSensor)
{
    if (whichSensor == left) {
        sensor_data.SENSOR_DATA_LeftBumper = read_bumper_sensor_pin_left();
        // printf("left bumper: %d ",sensor_data.SENSOR_DATA_LeftBumper);
    }
    else {
        sensor_data.SENSOR_DATA_RightBumper = read_bumper_sensor_pin_right();
        // printf("right bumper: %d \n",sensor_data.SENSOR_DATA_RightBumper);
    }
}

void calibrate_sensors(sensor_position whichSensor)
{
    if (whichSensor == left) {
        // Conevert the ADC reading to distance between the obstacles and the car in cm.
        int left_value = 0.3182 * adc0_get_reading(3) - 0.3959;

        // Set a maximum distance to 255cm (2.55m).
        if (left_value >= 255) {
            left_value = 255;
        }
        // put the new distance value into the queue and get the median value from the queue.
        int median = queue__update_and_get_median(&left_ultrasonic, left_value);
        // put the median value into can message.
        sensor_data.SENSOR_DATA_LeftUltrasonic = median;
        printf("left: %dcm ", median);
    }
    else if (whichSensor == right) {

        int right_value = 0.3182 * adc0_get_reading(5) - 0.3959;
        if (right_value >= 255) {
            right_value = 255;
        }
        int median = queue__update_and_get_median(&right_ultrasonic, right_value);
        sensor_data.SENSOR_DATA_RightUltrasonic = median;
        printf("right: %dcm ", median);
    }
    else if (whichSensor == rear) {

           uint16_t ir_value = 227648 * pow(adc0_get_reading(2), -1.27);
           if(ir_value >= 10){
           int average = queue__update_and_get_average(&rear_ir, ir_value);
           sensor_data.SENSOR_DATA_RearIr = average;

        }
           printf("rear: %d \n", ir_value);
    }

    else if (whichSensor == middle) {

        uint16_t middle_value = 0.3182 * adc0_get_reading(4) - 0.3959;
       // uint8_t middle_value = get_distance_cm_middle_ultrasonic();
        int median = queue__update_and_get_median(&middle_ultrasonic, middle_value);
        sensor_data.SENSOR_DATA_MiddleUltrasonic = median;
        printf("middle: %dcm ", median);
    }
}

