#ifndef PID_H_
#define PID_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <math.h>

// parameters table provided to modify 
// pwm and speed macros
// -------------------------------------------------------
#define MAX_PWM (255)
#define MID_PWM (125)
#define MIN_PWM (30)

#define MAX_SPEED (100)
#define MID_SPEED (100) //checked
#define MIN_SPEED (0)

// speed calculation macros
#define MIN_PIXEL (3)
#define MAX_PIXEL (180)
#define FORWARD_PIXEL (90)

#define MAX_BACKWARD_DISTANCE (80)
#define DECELERATION_DISTANCE (10)
#define MIN_DISTANCE (2.5)

#define MIN_ANGLE (10)
#define WIDTH (5)

// speed calculation paremeters
static const float corresponding_angle = 0.55; // checked

// PID const parameters
static const float kp_motor = 33;
static const float ki_motor = 0.038;
static const float kd_motor = 0.04;

//--------------------------------------------------------

// 0 for left front wheel, 1 for right front wheel
// 2 for right back wheel, 3 for left back wheel
extern int speed_on_wheels[4];  

// private 
void set_speed_on_wheels(int decision_coefficient, int direction_coefficient, int distance_coefficient);

// public

// called in unordered stage
void set_forward_velocity(int expected_pixel, double distance);
void set_spin_velocity();
void set_stop_velocity();
void set_backward_velocity();

// called in ordered stage 
void set_pan_right_velocity();
void set_pan_left_velocity();
void set_collecting_velocity(int angle);

#endif