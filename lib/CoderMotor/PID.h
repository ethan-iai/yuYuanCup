#ifndef PID_H_
#define PID_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

// parameters table provided to modify 
// pwm and speed macros
#define MAX_PWM (250)
#define MID_PWM (125)
#define MIN_PWM (0)
#define MAX_SPEED (100)
#define MIN_SPEED (0)

// speed calculation macros
#define MIN_PIXEL (3)
#define DECELERATION_DISTANCE (10)
#define MIN_DISTANCE (5)

// speed calculation paremeters
static const float corresponding_angle = 0.2;

// PID const parameters
static const float kp_motor = 33;
static const float ki_motor = 0.038;
static const float kd_motor = 0.04;

// PID variables 
static float error[10] = {0};
static float de = 0;

 //需要读 old pwm? 
static int pwm_old = 0;
static int pwm_cur = 0;

// 0 for left front wheel, 1 for right front wheel
// 2 for right rear wheel, 3 for left rear wheel
static int speed_on_wheels[4];  

// private 
void get_speed_on_wheels(int decision_coefficient, int direction_coefficient, int distance_coefficient);

// public
int get_PID_internal(double expected_speed, double cur_speed);
void get_expected_velocity(int expected_pixel, double distance);


#endif