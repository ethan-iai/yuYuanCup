#ifndef PID_H_
#define PID_H_

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

// parameters table provided to modify 
// pwm and speed parameters
#define MAX_PWM (250)
#define MID_PWM (125)
#define MIN_PWM (0)
#define MAX_SPEED (100)
#define MIN_SPEED (0)

// PID parameters
static const float kp_motor = 33;
static const float ki_motor = 0.038;
static const float kd_motor = 0.04;

// PID variables 
static float error[10] = {0};
static float de = 0;

 //需要读 old pwm? 
static int pwm_old = 0;
static int pwm_cur = 0;


int get_PID_internal(double expected_speed, double cur_speed);

#endif