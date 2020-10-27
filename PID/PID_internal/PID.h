#ifndef PID_H_
#define PID_H_

// parameters table provided to modify 
// pwm and speed parameters
#define max_pwm 250
#define mid_pwm 125
#define min_pwm 0
#define max_speed 100
#define min_speed 0

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